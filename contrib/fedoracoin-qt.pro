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

#    gui \
#    printsupport \

RESOURCES += \
    ../src/qt/bitcoin.qrc \
    ../src/qt/fedoracoin.qrc
    
#allows qt to complile with programs over 32k in size (limit should be 64k on Windows)
#  also have option regarding EXE output on errors (fedora's code is messy)
if(win32-g++*:if(CONFIG(debug, debug|release))) {
  QMAKE_CXXFLAGS += -Wa,-mbig-obj
  QMAKE_AR += --noinhibit-exec
}
