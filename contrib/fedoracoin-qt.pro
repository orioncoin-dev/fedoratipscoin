SOURCES += ../src/main.cpp \
           ../src/addrman.cpp \
           ../src/crypter.cpp \
           ../src/noui.cpp \
           ../src/scrypt.cpp \
           ../src/alert.cpp \
           ../src/db.cpp \
           ../src/protocol.cpp \
           ../src/scrypt-sse2.cpp \
           ../src/allocators.cpp \
           ../src/rpcblockchain.cpp \
           ../src/stealth.cpp \
           ../src/auxpow.cpp \
           ../src/rpcclient.cpp \
           ../src/sync.cpp \
           ../src/base58.cpp \
           ../src/hash.cpp \
           ../src/rpcdump.cpp \
           ../src/txdb.cpp \
           ../src/init.cpp \
           ../src/rpcmining.cpp \
           ../src/txmempool.cpp \
           ../src/key.cpp \
           ../src/rpcmisc.cpp \
           ../src/util.cpp \
           ../src/bloom.cpp \
           ../src/keystore.cpp \
           ../src/rpcnet.cpp \
           ../src/version.cpp \
           ../src/chainparams.cpp \
           ../src/leveldbwrapper.cpp \
           ../src/rpcprotocol.cpp \
           ../src/wallet.cpp \
           ../src/checkpoints.cpp \
           ../src/rpcrawtransaction.cpp \
           ../src/walletdb.cpp \
           ../src/checkpointsync.cpp \
           ../src/miner.cpp \
           ../src/rpcserver.cpp \
           ../src/coins.cpp \
           ../src/netbase.cpp \
           ../src/rpcwallet.cpp \
           ../src/core.cpp \
           ../src/net.cpp \
           ../src/script.cpp \

FORMS += \
    ../src/qt/forms/aboutdialog.ui \
    ../src/qt/forms/addressbookpage.ui \
    ../src/qt/forms/askpassphrasedialog.ui \
    ../src/qt/forms/coincontroldialog.ui \
    ../src/qt/forms/editaddressdialog.ui \
    ../src/qt/forms/helpmessagedialog.ui \
    ../src/qt/forms/intro.ui \
    ../src/qt/forms/openuridialog.ui \
    ../src/qt/forms/optionsdialog.ui \
    ../src/qt/forms/overviewpage.ui \
    ../src/qt/forms/qrcodedialog.ui \
    ../src/qt/forms/receivecoinsdialog.ui \
    ../src/qt/forms/receiverequestdialog.ui \
    ../src/qt/forms/rpcconsole.ui \
    ../src/qt/forms/sendcoinsdialog.ui \
    ../src/qt/forms/sendcoinsentry.ui \
    ../src/qt/forms/shiftdialog.ui \
    ../src/qt/forms/signverifymessagedialog.ui \
    ../src/qt/forms/snapwidget.ui \
    ../src/qt/forms/transactiondescdialog.ui \

LIBS += \
-L"$$(STAGING)\lib" \

QT += \
    qtwidgets \
    core \
    gui \
    printsupport \

RESOURCES += \
    ../src/qt/fedoracoin.qrc
    
#allows qt to complile with programs over 32k in size (limit should be 64k on Windows)
#  also have option regarding EXE output on errors (fedora's code is messy)
if(win32-g++*:if(CONFIG(debug, debug|release))) {
  QMAKE_CXXFLAGS += -Wa,-mbig-obj
  QMAKE_AR += --noinhibit-exec
}
