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

TRANSLATIONS += \
    qt/locale/bitcoin_ach.ts \
    qt/locale/bitcoin_af_ZA.ts \
    qt/locale/bitcoin_ar.ts \
    qt/locale/bitcoin_be_BY.ts \
    qt/locale/bitcoin_bg.ts \
    qt/locale/bitcoin_bs.ts \
    qt/locale/bitcoin_ca_ES.ts \
    qt/locale/bitcoin_ca.ts \
    qt/locale/bitcoin_ca@valencia.ts \
    qt/locale/bitcoin_cmn.ts \
    qt/locale/bitcoin_cs.ts \
    qt/locale/bitcoin_cy.ts \
    qt/locale/bitcoin_da.ts \
    qt/locale/bitcoin_de.ts \
    qt/locale/bitcoin_el_GR.ts \
    qt/locale/bitcoin_en.ts \
    qt/locale/bitcoin_eo.ts \
    qt/locale/bitcoin_es_CL.ts \
    qt/locale/bitcoin_es_DO.ts \
    qt/locale/bitcoin_es_MX.ts \
    qt/locale/bitcoin_es.ts \
    qt/locale/bitcoin_es_UY.ts \
    qt/locale/bitcoin_et.ts \
    qt/locale/bitcoin_eu_ES.ts \
    qt/locale/bitcoin_fa_IR.ts \
    qt/locale/bitcoin_fa.ts \
    qt/locale/bitcoin_fi.ts \
    qt/locale/bitcoin_fr_CA.ts \
    qt/locale/bitcoin_fr.ts \
    qt/locale/bitcoin_gl.ts \
    qt/locale/bitcoin_gu_IN.ts \
    qt/locale/bitcoin_he.ts \
    qt/locale/bitcoin_hi_IN.ts \
    qt/locale/bitcoin_hr.ts \
    qt/locale/bitcoin_hu.ts \
    qt/locale/bitcoin_id_ID.ts \
    qt/locale/bitcoin_it.ts \
    qt/locale/bitcoin_ja.ts \
    qt/locale/bitcoin_ka.ts \
    qt/locale/bitcoin_kk_KZ.ts \
    qt/locale/bitcoin_ko_KR.ts \
    qt/locale/bitcoin_ky.ts \
    qt/locale/bitcoin_la.ts \
    qt/locale/bitcoin_lt.ts \
    qt/locale/bitcoin_lv_LV.ts \
    qt/locale/bitcoin_mn.ts \
    qt/locale/bitcoin_ms_MY.ts \
    qt/locale/bitcoin_nb.ts \
    qt/locale/bitcoin_nl.ts \
    qt/locale/bitcoin_pam.ts \
    qt/locale/bitcoin_pl.ts \
    qt/locale/bitcoin_pt_BR.ts \
    qt/locale/bitcoin_pt_PT.ts \
    qt/locale/bitcoin_ro_RO.ts \
    qt/locale/bitcoin_ru.ts \
    qt/locale/bitcoin_sah.ts \
    qt/locale/bitcoin_sk.ts \
    qt/locale/bitcoin_sl_SI.ts \
    qt/locale/bitcoin_sq.ts \
    qt/locale/bitcoin_sr.ts \
    qt/locale/bitcoin_sv.ts \
    qt/locale/bitcoin_th_TH.ts \
    qt/locale/bitcoin_tr.ts \
    qt/locale/bitcoin_uk.ts \
    qt/locale/bitcoin_ur_PK.ts \
    qt/locale/bitcoin_uz@Cyrl.ts \
    qt/locale/bitcoin_vi.ts \
    qt/locale/bitcoin_vi_VN.ts \
    qt/locale/bitcoin_zh_CN.ts \
    qt/locale/bitcoin_zh_HK.ts \
    qt/locale/bitcoin_zh_TW.ts \

LIBS += \
-L"$$(STAGING)\lib" \

QT += \
    widgets \
    core \
    gui \
    printsupport \

RESOURCES += \
    ../src/qt/fedoracoin.qrc 

!contains(QMAKE_EXTRA_COMPILERS, updateqm) {
    updateqm.input         = TRANSLATIONS
    updateqm.output        = qt/locale/${QMAKE_FILE_BASE}.qm
    updateqm.commands      = $$[QT_INSTALL_BINS]/lrelease -idbased ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_BASE}.qm
    updateqm.CONFIG       += no_link target_predeps
    QMAKE_EXTRA_COMPILERS += updateqm
    PRE_TARGETDEPS        += compiler_updateqm_make_all
}

greaterThan(QT_MAJOR_VERSION, 4) {

        QT += widgets
        DEFINES += HAVE_QT5
    }
    
#allows qt to complile with programs over 32k in size (limit should be 64k on Windows)
#  also have option regarding EXE output on errors (fedora's code is messy)
if(win32-g++*:if(CONFIG(debug, debug|release))) {
  QMAKE_CXXFLAGS += -Wa,-mbig-obj
  QMAKE_AR += --noinhibit-exec
}
