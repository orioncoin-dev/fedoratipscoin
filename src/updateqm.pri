!contains(QMAKE_EXTRA_COMPILERS, updateqm) {
    updateqm.input         = TRANSLATIONS
    updateqm.output        = qt/locale/${QMAKE_FILE_BASE}.qm
    updateqm.commands      = $$[QT_INSTALL_BINS]/lrelease -idbased ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_BASE}.qm
    updateqm.CONFIG       += no_link target_predeps
    QMAKE_EXTRA_COMPILERS += updateqm
    PRE_TARGETDEPS        += compiler_updateqm_make_all 
}
