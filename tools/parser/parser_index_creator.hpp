//
//  parser_index_creator.hpp
//  blocksci_parser
//
//  Created by Harry Kalodner on 9/22/17.
//

#ifndef parser_index_creator_hpp
#define parser_index_creator_hpp

#include "parser_configuration.hpp"
#include "parser_fwd.hpp"

#include <future>

namespace blocksci {
    struct State;
}

template <typename IndexType>
class ParserIndexCreator {
private:
    const ParserConfigurationBase &config;
    std::future<void> updateFuture;
    std::future<void> teardownFuture;
    std::atomic<bool> launchingUpdate;
    std::atomic<bool> tornDown;
    IndexType index;
    
public:
    ParserIndexCreator(const ParserConfigurationBase &config_, const std::string &path) : config(config_), updateFuture{std::async(std::launch::async, [&] {})}, launchingUpdate(false), tornDown(false), index(config, path) {}
    ParserIndexCreator(const ParserIndexCreator &) = delete;
    ParserIndexCreator &operator=(const ParserIndexCreator &) = delete;
    ParserIndexCreator(ParserIndexCreator &&) = delete;
    ParserIndexCreator &operator=(ParserIndexCreator &&) = delete;
    
    ~ParserIndexCreator() {
        if (!tornDown) {
            blocksci::ChainAccess chain{config, false, 0};
            blocksci::ScriptAccess scripts{config};
            blocksci::State updateState{chain, scripts};
            complete(updateState);
        }
        teardownFuture.get();
    }
    
    void update(blocksci::State state) {
        using namespace std::chrono_literals;
        
        if (updateFuture.wait_for(0ms) == std::future_status::ready) {
            updateFuture.get();
            launchingUpdate = true;
            updateFuture = std::async(std::launch::async, [this, state] {
                index.runUpdate(state);
                launchingUpdate = false;
            });
        }
    }
    
    void complete(blocksci::State state) {
        using namespace std::chrono_literals;
        assert(!tornDown);
        tornDown = true;
        teardownFuture = std::async(std::launch::async, [&, state] {
            while (launchingUpdate) {
                std::this_thread::sleep_for(100ms);
            }
            if (updateFuture.valid()) {
                updateFuture.get();
            }
            index.runUpdate(state);
        });
    }
};

#endif /* parser_index_creator_hpp */
