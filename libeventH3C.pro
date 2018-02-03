TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    libeventstr/strlcpy.c \
    libeventstr/signal.c \
    libeventstr/select.c \
    libeventstr/poll.c \
    libeventstr/log.c \
    libeventstr/http.c \
    libeventstr/evutil.c \
    libeventstr/evrpc.c \
    libeventstr/event_tagging.c \
    libeventstr/event.c \
    libeventstr/evdns.c \
    libeventstr/evbuffer.c \
    libeventstr/epoll_sub.c \
    libeventstr/epoll.c \
    libeventstr/buffer.c \
    libeventor.cpp \
    LightLoger.cpp \
    univiewanalyze.cpp \
    common.cpp \
    XmlOpertator.cpp \
    tinyxmlparser.cpp \
    tinyxmlerror.cpp \
    tinyxml.cpp \
    tinystr.cpp \
    mempoolstr/ncx_slab.c \



HEADERS += \
    libeventor.h \
    LightLoger.h \
    libeventstr/strlcpy-internal.h \
    libeventstr/min_heap.h \
    libeventstr/http-internal.h \
    libeventstr/evutil.h \
    libeventstr/evsignal.h \
    libeventstr/evrpc-internal.h \
    libeventstr/evrpc.h \
    libeventstr/evhttp.h \
    libeventstr/event-internal.h \
    libeventstr/event-config.h \
    libeventstr/event.h \
    libeventstr/evdns.h \
    libeventstr/config.h \
    univiewanalyze.h \
    common.h \
    XmlOpertator.h \
    tinyxml.h \
    tinystr.h \
    mempoolstr/ncx_core.h \
    mempoolstr/ncx_lock.h \
    mempoolstr/ncx_log.h \
    mempoolstr/ncx_slab.h \



unix|win32: LIBS += -lpthread
