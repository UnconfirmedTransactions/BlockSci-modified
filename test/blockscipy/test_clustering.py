import blocksci
from util import sorted_tx_list


def test_clustering_default_heuristic(chain, tmpdir_factory):
    """Tests that we can run create_clustering with path and chain only"""
    blocksci.cluster.ClusterManager.create_clustering(
        str(tmpdir_factory.mktemp("clustering_default_heuristic")), chain
    )


def test_clustering_proxy_heuristic(chain, tmpdir_factory):
    """Tests that we can run create_clustering with a proxy heuristic"""

    # output index 0
    heuristic = blocksci.heuristics.change.ChangeHeuristic(
        blocksci.Tx._self_proxy.outputs.where(lambda o: o.index == 0)
    )
    cm = blocksci.cluster.ClusterManager.create_clustering(
        str(tmpdir_factory.mktemp("clustering_proxy_heuristic_0")),
        chain,
        heuristic=heuristic,
    )
    for tx in chain.blocks.txes:
        if tx.input_count > 0 and not blocksci.heuristics.is_coinjoin(tx):
            cluster = cm.cluster_with_address(tx.inputs[0].address)
            addresses = cluster.addresses.to_list()
            assert tx.outputs[0].address in addresses

    # output index 1
    heuristic = blocksci.heuristics.change.ChangeHeuristic(
        blocksci.Tx._self_proxy.outputs.where(lambda o: o.index == 1)
    )
    cm = blocksci.cluster.ClusterManager.create_clustering(
        str(tmpdir_factory.mktemp("clustering_proxy_heuristic_1")),
        chain,
        heuristic=heuristic,
    )
    for tx in chain.blocks.txes:
        if (
            tx.input_count > 0
            and tx.output_count > 1
            and not blocksci.heuristics.is_coinjoin(tx)
        ):
            cluster = cm.cluster_with_address(tx.inputs[0].address)
            addresses = cluster.addresses.to_list()
            assert tx.outputs[1].address in addresses


def test_clustering_no_change(chain, json_data, regtest, tmpdir_factory):
    cm = blocksci.cluster.ClusterManager.create_clustering(
        str(tmpdir_factory.mktemp("clustering")),
        chain,
        heuristic=blocksci.heuristics.change.none,
    )
    cluster = cm.cluster_with_address(
        chain.address_from_string(json_data["merge-addr-1"])
    )

    assert 3 == len(cluster.addresses.to_list())
    assert 3 == cluster.address_count()

    assert (
        chain.address_from_string(json_data["merge-addr-1"])
        in cluster.addresses.to_list()
    )
    assert (
        chain.address_from_string(json_data["merge-addr-2"])
        in cluster.addresses.to_list()
    )
    assert (
        chain.address_from_string(json_data["merge-addr-3"])
        in cluster.addresses.to_list()
    )

    assert cluster.index >= 0

    print(cluster.addresses.to_list(), file=regtest)
    print(cluster.balance(), file=regtest)
    print(cluster.balance(100), file=regtest)
    print(cluster.count_of_type(blocksci.address_type.pubkeyhash), file=regtest)
    print(cluster.count_of_type(blocksci.address_type.scripthash), file=regtest)
    print(cluster.count_of_type(blocksci.address_type.witness_pubkeyhash), file=regtest)
    print(cluster.count_of_type(blocksci.address_type.witness_scripthash), file=regtest)
    print(cluster.count_of_type(blocksci.address_type.witness_taproothash), file=regtest)
    print(sorted_tx_list(cluster.input_txes()), file=regtest)
    print(cluster.input_txes_count(), file=regtest)
    print(cluster.inputs().to_list(), file=regtest)
    print(sorted_tx_list(cluster.txes()), file=regtest)
    print(sorted_tx_list(cluster.output_txes()), file=regtest)
    print(cluster.output_txes_count(), file=regtest)
    print(cluster.outputs().to_list(), file=regtest)
    print(cluster.address_count(), file=regtest)
    print(cluster.txes(), file=regtest)
    print(cluster.type_equiv_size, file=regtest)

    for tx in chain.blocks.txes:
        if tx.input_count > 1 and not blocksci.heuristics.is_coinjoin(tx):
            cluster = cm.cluster_with_address(tx.inputs[0].address)
            addresses = cluster.addresses.to_list()
            for i in range(tx.input_count):
                assert tx.inputs[i].address in addresses

    cluster_regtest(chain, json_data, regtest, cm)


def test_clustering_with_change(chain, json_data, tmpdir_factory, regtest):
    heuristics = [
        blocksci.heuristics.change.peeling_chain.unique_change,
        blocksci.heuristics.change.optimal_change.unique_change,
        blocksci.heuristics.change.address_type.unique_change,
        blocksci.heuristics.change.locktime.unique_change,
        blocksci.heuristics.change.address_reuse.unique_change,
        blocksci.heuristics.change.client_change_address_behavior.unique_change,
        blocksci.heuristics.change.legacy.unique_change,
        blocksci.heuristics.change.none,
    ]

    for f in heuristics:
        cm = blocksci.cluster.ClusterManager.create_clustering(
            str(tmpdir_factory.mktemp("clustering")), chain, heuristic=f
        )
        cluster = cm.cluster_with_address(
            chain.address_from_string(json_data["merge-addr-1"])
        )

        assert 3 <= len(cluster.addresses.to_list())

        assert (
            chain.address_from_string(json_data["merge-addr-1"])
            in cluster.addresses.to_list()
        )
        assert (
            chain.address_from_string(json_data["merge-addr-2"])
            in cluster.addresses.to_list()
        )
        assert (
            chain.address_from_string(json_data["merge-addr-3"])
            in cluster.addresses.to_list()
        )

        assert cluster.index >= 0

        cluster_regtest(chain, json_data, regtest, cm)


def test_clustering_composability(chain, tmpdir_factory):
    nofunc = blocksci.heuristics.change.none
    compfunc = (
        blocksci.heuristics.change.legacy - blocksci.heuristics.change.legacy
    ).unique_change

    cm1 = blocksci.cluster.ClusterManager.create_clustering(
        str(tmpdir_factory.mktemp("clustering")), chain, heuristic=nofunc
    )
    cm2 = blocksci.cluster.ClusterManager.create_clustering(
        str(tmpdir_factory.mktemp("clustering")), chain, heuristic=compfunc
    )

    for cl in cm1.clusters():
        if cl.address_count() > 0:
            a = cl.addresses.to_list()[0]
            other_cluster = cm2.cluster_with_address(a)
            assert cl.address_count() == other_cluster.address_count()
            assert set(cl.addresses.to_list()) == set(other_cluster.addresses.to_list())


def test_clustering_ignore_coinjoin(chain, json_data, tmpdir_factory, regtest):
    addresses = (
        chain.tx_with_hash(json_data["simple-coinjoin-tx"])
        .inputs.map(lambda i: i.address)
        .to_list()
    )

    cm = blocksci.cluster.ClusterManager.create_clustering(
        str(tmpdir_factory.mktemp("clustering")),
        chain,
        heuristic=blocksci.heuristics.change.none,
        ignore_coinjoin=True,
    )
    cluster = cm.cluster_with_address(addresses[0])
    cluster_addresses = cluster.addresses.to_list()
    assert 1 == len(cluster)

    for addr in addresses[1:]:
        assert addr not in cluster_addresses

    # Normal clustering should still work as expected
    cluster = cm.cluster_with_address(
        chain.address_from_string(json_data["merge-addr-1"])
    )
    assert 3 <= len(cluster.addresses.to_list())

    assert (
        chain.address_from_string(json_data["merge-addr-1"])
        in cluster.addresses.to_list()
    )
    assert (
        chain.address_from_string(json_data["merge-addr-2"])
        in cluster.addresses.to_list()
    )
    assert (
        chain.address_from_string(json_data["merge-addr-3"])
        in cluster.addresses.to_list()
    )

    cluster_regtest(chain, json_data, regtest, cm)


def test_clustering_cluster_coinjoin(chain, json_data, tmpdir_factory, regtest):
    addresses = (
        chain.tx_with_hash(json_data["simple-coinjoin-tx"])
        .inputs.map(lambda i: i.address)
        .to_list()
    )

    cm = blocksci.cluster.ClusterManager.create_clustering(
        str(tmpdir_factory.mktemp("clustering")),
        chain,
        heuristic=blocksci.heuristics.change.none,
        ignore_coinjoin=False,
    )
    cluster = cm.cluster_with_address(addresses[0])
    cluster_addresses = cluster.addresses.to_list()
    assert 1 < len(cluster)

    for addr in addresses:
        assert addr in cluster_addresses

    # Normal clustering should still work as expected
    cluster = cm.cluster_with_address(
        chain.address_from_string(json_data["merge-addr-1"])
    )
    assert 3 <= len(cluster.addresses.to_list())

    assert (
        chain.address_from_string(json_data["merge-addr-1"])
        in cluster.addresses.to_list()
    )
    assert (
        chain.address_from_string(json_data["merge-addr-2"])
        in cluster.addresses.to_list()
    )
    assert (
        chain.address_from_string(json_data["merge-addr-3"])
        in cluster.addresses.to_list()
    )

    cluster_regtest(chain, json_data, regtest, cm)


def cluster_regtest(chain, json_data, regtest, cm):
    ids = [
        "address-p2pkh-spend-1",
        "address-p2sh-spend-2",
        "addr-2-in-2-out",
        "addr-peeling-chain",
        "addr-merge-0",
        "addr-merge-2",
        "merge-addr-1",
        "merge-addr-2",
    ]
    addresses = [chain.address_from_string(json_data[x]) for x in ids]
    for addr in addresses:
        cluster = cm.cluster_with_address(addr)
        print(
            sorted(cluster.addresses.to_list(), key=lambda x: x.address_num),
            file=regtest,
        )


def test_tagged_address(chain, tmpdir_factory):
    cm = blocksci.cluster.ClusterManager.create_clustering(
        str(tmpdir_factory.mktemp("tagged-address-test")),
        chain,
        heuristic=blocksci.heuristics.change.none
    )
    address = chain[-1].txes[0].outputs[0].address
    cluster = cm.cluster_with_address(address)
    tags = {address: "test-tag"}
    assert cluster.tagged_addresses(tags).size == 1
    assert cluster.tagged_addresses(tags).to_list()[0].address == address
    assert cluster.tagged_addresses(tags).to_list()[0].tag == "test-tag"
