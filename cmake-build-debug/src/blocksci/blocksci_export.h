
#ifndef BLOCKSCI_EXPORT_H
#define BLOCKSCI_EXPORT_H

#ifdef BLOCKSCI_STATIC_DEFINE
#  define BLOCKSCI_EXPORT
#  define BLOCKSCI_NO_EXPORT
#else
#  ifndef BLOCKSCI_EXPORT
#    ifdef blocksci_EXPORTS
        /* We are building this library */
#      define BLOCKSCI_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define BLOCKSCI_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef BLOCKSCI_NO_EXPORT
#    define BLOCKSCI_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef BLOCKSCI_DEPRECATED
#  define BLOCKSCI_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef BLOCKSCI_DEPRECATED_EXPORT
#  define BLOCKSCI_DEPRECATED_EXPORT BLOCKSCI_EXPORT BLOCKSCI_DEPRECATED
#endif

#ifndef BLOCKSCI_DEPRECATED_NO_EXPORT
#  define BLOCKSCI_DEPRECATED_NO_EXPORT BLOCKSCI_NO_EXPORT BLOCKSCI_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef BLOCKSCI_NO_DEPRECATED
#    define BLOCKSCI_NO_DEPRECATED
#  endif
#endif

#endif /* BLOCKSCI_EXPORT_H */
