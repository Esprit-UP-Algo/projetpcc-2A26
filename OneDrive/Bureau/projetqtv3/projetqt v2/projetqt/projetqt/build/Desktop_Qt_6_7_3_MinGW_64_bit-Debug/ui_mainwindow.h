/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QFrame *frame_2;
    QPushButton *pushButton;
    QLabel *lblClients;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *headerLayout;
    QPushButton *btnListeClients_3;
    QPushButton *btnAjouterClient_3;
    QLabel *lblListeClients;
    QHBoxLayout *searchLayout;
    QFrame *frame_7;
    QToolButton *toolButton_6;
    QToolButton *toolButton_7;
    QToolButton *toolButton_8;
    QToolButton *toolButton_9;
    QToolButton *toolButton_10;
    QLineEdit *searchLineEdit;
    QPushButton *btnRechercher;
    QComboBox *comboProfession;
    QPushButton *btnFilter;
    QTableWidget *tableClients;
    QPushButton *btnExporter;
    QHBoxLayout *actionButtonsLayout;
    QFrame *frame_6;
    QToolButton *toolButton_16;
    QToolButton *toolButton_17;
    QToolButton *toolButton_18;
    QToolButton *toolButton_19;
    QToolButton *toolButton_20;
    QWidget *page_2;
    QWidget *page_21;
    QFrame *frameFicheClient;
    QLabel *lblFicheClient;
    QLabel *label;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QWidget *layoutWidget;
    QHBoxLayout *ajouterActionLayout;
    QPushButton *btnConfirmer;
    QPushButton *btnAnnuler;
    QLineEdit *lineEditNom;
    QLineEdit *lineEditPhone;
    QCheckBox *checkNew;
    QLineEdit *lineEditDateNaissance;
    QLineEdit *lineEditID;
    QLineEdit *lineEditPrenom;
    QCheckBox *checkOld;
    QCheckBox *checkVIP;
    QComboBox *comboSexe;
    QLabel *label_2;
    QTextEdit *textEdit;
    QLabel *label_3;
    QPushButton *btnListeClients_2;
    QPushButton *btnAjouterClient_2;
    QFrame *frame_5;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *toolButton_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1171, 719);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(20, 20, 1131, 611));
        page = new QWidget();
        page->setObjectName("page");
        frame_2 = new QFrame(page);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(940, 0, 201, 611));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        pushButton = new QPushButton(frame_2);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 10, 141, 31));
        pushButton->setStyleSheet(QString::fromUtf8("background-color:#0984e3;color:white;font-weight:bold;border-radius:15px;padding:8px 24px;font-size:15px;"));
        lblClients = new QLabel(frame_2);
        lblClients->setObjectName("lblClients");
        lblClients->setGeometry(QRect(-700, 104, 711, 511));
        frame = new QFrame(page);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(170, 0, 771, 611));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");
        btnListeClients_3 = new QPushButton(frame);
        btnListeClients_3->setObjectName("btnListeClients_3");
        btnListeClients_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #41375f;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    border-radius: 15px;\n"
"    padding: 12px 24px;\n"
"    font-size: 15px;\n"
"    border: 2px solid #41375f;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #5a4a82;\n"
"    border: 2px solid #7158a0;\n"
"}"));

        headerLayout->addWidget(btnListeClients_3);

        btnAjouterClient_3 = new QPushButton(frame);
        btnAjouterClient_3->setObjectName("btnAjouterClient_3");
        btnAjouterClient_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #41375f;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    border-radius: 15px;\n"
"    padding: 12px 24px;\n"
"    font-size: 15px;\n"
"    border: 2px solid #41375f;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #5a4a82;\n"
"    border: 2px solid #7158a0;\n"
"}"));

        headerLayout->addWidget(btnAjouterClient_3);


        verticalLayout->addLayout(headerLayout);

        lblListeClients = new QLabel(frame);
        lblListeClients->setObjectName("lblListeClients");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        lblListeClients->setFont(font);
        lblListeClients->setStyleSheet(QString::fromUtf8("color:#2d224c;font-weight:bold;margin:16px 0 8px 0;\n"
"background-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(lblListeClients);

        searchLayout = new QHBoxLayout();
        searchLayout->setObjectName("searchLayout");
        frame_7 = new QFrame(frame);
        frame_7->setObjectName("frame_7");
        frame_7->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 124);; border-radius:20px;"));
        frame_7->setFrameShape(QFrame::Shape::StyledPanel);
        frame_7->setFrameShadow(QFrame::Shadow::Raised);
        toolButton_6 = new QToolButton(frame_7);
        toolButton_6->setObjectName("toolButton_6");
        toolButton_6->setGeometry(QRect(20, 240, 141, 41));
        toolButton_6->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC); }"));
        toolButton_7 = new QToolButton(frame_7);
        toolButton_7->setObjectName("toolButton_7");
        toolButton_7->setGeometry(QRect(20, 300, 141, 41));
        toolButton_7->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC); }"));
        toolButton_8 = new QToolButton(frame_7);
        toolButton_8->setObjectName("toolButton_8");
        toolButton_8->setGeometry(QRect(20, 360, 141, 41));
        toolButton_8->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC); }"));
        toolButton_9 = new QToolButton(frame_7);
        toolButton_9->setObjectName("toolButton_9");
        toolButton_9->setGeometry(QRect(20, 420, 141, 41));
        toolButton_9->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC); }"));
        toolButton_10 = new QToolButton(frame_7);
        toolButton_10->setObjectName("toolButton_10");
        toolButton_10->setGeometry(QRect(20, 180, 141, 41));
        toolButton_10->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC); }\n"
""));

        searchLayout->addWidget(frame_7);

        searchLineEdit = new QLineEdit(frame);
        searchLineEdit->setObjectName("searchLineEdit");

        searchLayout->addWidget(searchLineEdit);

        btnRechercher = new QPushButton(frame);
        btnRechercher->setObjectName("btnRechercher");

        searchLayout->addWidget(btnRechercher);

        comboProfession = new QComboBox(frame);
        comboProfession->addItem(QString());
        comboProfession->setObjectName("comboProfession");
        comboProfession->setEditable(false);

        searchLayout->addWidget(comboProfession);

        btnFilter = new QPushButton(frame);
        btnFilter->setObjectName("btnFilter");

        searchLayout->addWidget(btnFilter);


        verticalLayout->addLayout(searchLayout);

        tableClients = new QTableWidget(frame);
        if (tableClients->columnCount() < 8)
            tableClients->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableClients->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableClients->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableClients->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableClients->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableClients->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableClients->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableClients->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableClients->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableClients->setObjectName("tableClients");
        tableClients->setStyleSheet(QString::fromUtf8("/*QHeaderView::section { background-color:#2d224c;color:white;font-weight:bold; } QTableWidget { background-color:white; }*/\n"
"QTableWidget {\n"
"    background-color: white;\n"
"	color: rgb(0, 0, 0);\n"
"    border-radius: 10px;\n"
"    gridline-color: #dfe6e9;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #2d224c;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    padding: 8px;\n"
"    border: none;\n"
"}\n"
"QTableWidget::item {\n"
"    padding: 8px;\n"
"    border-bottom: 1px solid #dfe6e9;\n"
"}\n"
"QTableWidget::item:selected {\n"
"    background-color: #a29bfe;\n"
"    color: white;\n"
"}"));

        verticalLayout->addWidget(tableClients);

        btnExporter = new QPushButton(frame);
        btnExporter->setObjectName("btnExporter");

        verticalLayout->addWidget(btnExporter);

        actionButtonsLayout = new QHBoxLayout();
        actionButtonsLayout->setObjectName("actionButtonsLayout");

        verticalLayout->addLayout(actionButtonsLayout);


        horizontalLayout->addLayout(verticalLayout);

        frame_6 = new QFrame(page);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(-10, 60, 181, 541));
        frame_6->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 124);; border-radius:20px;"));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        toolButton_16 = new QToolButton(frame_6);
        toolButton_16->setObjectName("toolButton_16");
        toolButton_16->setGeometry(QRect(20, 240, 141, 41));
        toolButton_16->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_17 = new QToolButton(frame_6);
        toolButton_17->setObjectName("toolButton_17");
        toolButton_17->setGeometry(QRect(20, 300, 141, 41));
        toolButton_17->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_18 = new QToolButton(frame_6);
        toolButton_18->setObjectName("toolButton_18");
        toolButton_18->setGeometry(QRect(20, 360, 141, 41));
        toolButton_18->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_19 = new QToolButton(frame_6);
        toolButton_19->setObjectName("toolButton_19");
        toolButton_19->setGeometry(QRect(20, 420, 141, 41));
        toolButton_19->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_20 = new QToolButton(frame_6);
        toolButton_20->setObjectName("toolButton_20");
        toolButton_20->setGeometry(QRect(20, 180, 141, 41));
        toolButton_20->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        page_21 = new QWidget();
        page_21->setObjectName("page_21");
        frameFicheClient = new QFrame(page_21);
        frameFicheClient->setObjectName("frameFicheClient");
        frameFicheClient->setGeometry(QRect(210, 90, 841, 511));
        frameFicheClient->setStyleSheet(QString::fromUtf8("border:2px solid #a55eea; border-radius:20px; background-color:#f5f6fa;\n"
"border-color: rgb(0, 0, 127);"));
        lblFicheClient = new QLabel(frameFicheClient);
        lblFicheClient->setObjectName("lblFicheClient");
        lblFicheClient->setGeometry(QRect(190, 20, 481, 68));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        lblFicheClient->setFont(font1);
        lblFicheClient->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 127);"));
        lblFicheClient->setFrameShape(QFrame::Shape::StyledPanel);
        lblFicheClient->setFrameShadow(QFrame::Shadow::Raised);
        label = new QLabel(frameFicheClient);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 130, 91, 20));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        label_5 = new QLabel(frameFicheClient);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(60, 170, 91, 20));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        label_6 = new QLabel(frameFicheClient);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(60, 210, 91, 20));
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        label_7 = new QLabel(frameFicheClient);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(60, 250, 91, 20));
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        label_8 = new QLabel(frameFicheClient);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(60, 330, 91, 20));
        label_8->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        label_9 = new QLabel(frameFicheClient);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(60, 290, 91, 21));
        label_9->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        label_10 = new QLabel(frameFicheClient);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(60, 380, 121, 41));
        label_10->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        layoutWidget = new QWidget(frameFicheClient);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(580, 450, 240, 42));
        ajouterActionLayout = new QHBoxLayout(layoutWidget);
        ajouterActionLayout->setObjectName("ajouterActionLayout");
        ajouterActionLayout->setContentsMargins(0, 0, 0, 0);
        btnConfirmer = new QPushButton(layoutWidget);
        btnConfirmer->setObjectName("btnConfirmer");

        ajouterActionLayout->addWidget(btnConfirmer);

        btnAnnuler = new QPushButton(layoutWidget);
        btnAnnuler->setObjectName("btnAnnuler");

        ajouterActionLayout->addWidget(btnAnnuler);

        lineEditNom = new QLineEdit(frameFicheClient);
        lineEditNom->setObjectName("lineEditNom");
        lineEditNom->setGeometry(QRect(240, 170, 251, 26));
        lineEditNom->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEditPhone = new QLineEdit(frameFicheClient);
        lineEditPhone->setObjectName("lineEditPhone");
        lineEditPhone->setGeometry(QRect(240, 250, 251, 26));
        lineEditPhone->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        checkNew = new QCheckBox(frameFicheClient);
        checkNew->setObjectName("checkNew");
        checkNew->setGeometry(QRect(340, 390, 58, 24));
        checkNew->setStyleSheet(QString::fromUtf8("background-color: rgb(70, 88, 127);"));
        lineEditDateNaissance = new QLineEdit(frameFicheClient);
        lineEditDateNaissance->setObjectName("lineEditDateNaissance");
        lineEditDateNaissance->setGeometry(QRect(240, 290, 251, 26));
        lineEditDateNaissance->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEditID = new QLineEdit(frameFicheClient);
        lineEditID->setObjectName("lineEditID");
        lineEditID->setGeometry(QRect(240, 130, 251, 26));
        lineEditID->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEditPrenom = new QLineEdit(frameFicheClient);
        lineEditPrenom->setObjectName("lineEditPrenom");
        lineEditPrenom->setGeometry(QRect(240, 210, 251, 26));
        lineEditPrenom->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        checkOld = new QCheckBox(frameFicheClient);
        checkOld->setObjectName("checkOld");
        checkOld->setGeometry(QRect(250, 390, 52, 24));
        checkOld->setStyleSheet(QString::fromUtf8("background-color: rgb(70, 88, 127);"));
        checkVIP = new QCheckBox(frameFicheClient);
        checkVIP->setObjectName("checkVIP");
        checkVIP->setGeometry(QRect(440, 390, 49, 24));
        checkVIP->setStyleSheet(QString::fromUtf8("background-color: rgb(70, 88, 127);"));
        comboSexe = new QComboBox(frameFicheClient);
        comboSexe->addItem(QString());
        comboSexe->addItem(QString());
        comboSexe->setObjectName("comboSexe");
        comboSexe->setGeometry(QRect(240, 330, 251, 31));
        label_2 = new QLabel(frameFicheClient);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(620, 110, 161, 121));
        label_2->setStyleSheet(QString::fromUtf8("QLabel#photoClient {\n"
"    border: 3px dashed #6c5ce7;\n"
"    border-radius: 15px;\n"
"    background-color: #f8f9fa;\n"
"    min-width: 150px;\n"
"    min-height: 150px;\n"
"    max-width: 150px;\n"
"    max-height: 150px;\n"
"}\n"
"QLabel#photoClient:hover {\n"
"    border: 3px dashed #fd79a8;\n"
"    background-color: #e9ecef;\n"
"}"));
        textEdit = new QTextEdit(frameFicheClient);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(690, 310, 121, 31));
        textEdit->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    border: 2px solid #dfe6e9;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    background-color: white;\n"
"    font-size: 14px;\n"
"}\n"
"QTextEdit:focus {\n"
"    border: 2px solid #6c5ce7;\n"
"}"));
        label_3 = new QLabel(frameFicheClient);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(530, 310, 151, 20));
        label_3->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 127);\n"
""));
        btnListeClients_2 = new QPushButton(page_21);
        btnListeClients_2->setObjectName("btnListeClients_2");
        btnListeClients_2->setGeometry(QRect(210, 40, 360, 40));
        btnListeClients_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #41375f;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    border-radius: 15px;\n"
"    padding: 12px 24px;\n"
"    font-size: 15px;\n"
"    border: 2px solid #41375f;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #5a4a82;\n"
"    border: 2px solid #7158a0;\n"
"}"));
        btnAjouterClient_2 = new QPushButton(page_21);
        btnAjouterClient_2->setObjectName("btnAjouterClient_2");
        btnAjouterClient_2->setGeometry(QRect(670, 40, 360, 40));
        btnAjouterClient_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #41375f;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    border-radius: 15px;\n"
"    padding: 12px 24px;\n"
"    font-size: 15px;\n"
"    border: 2px solid #41375f;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #5a4a82;\n"
"    border: 2px solid #7158a0;\n"
"}"));
        frame_5 = new QFrame(page_21);
        frame_5->setObjectName("frame_5");
        frame_5->setGeometry(QRect(-10, 50, 181, 541));
        frame_5->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 124);; border-radius:20px;"));
        frame_5->setFrameShape(QFrame::Shape::StyledPanel);
        frame_5->setFrameShadow(QFrame::Shadow::Raised);
        toolButton = new QToolButton(frame_5);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(20, 240, 141, 41));
        toolButton->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_2 = new QToolButton(frame_5);
        toolButton_2->setObjectName("toolButton_2");
        toolButton_2->setGeometry(QRect(20, 300, 141, 41));
        toolButton_2->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_3 = new QToolButton(frame_5);
        toolButton_3->setObjectName("toolButton_3");
        toolButton_3->setGeometry(QRect(20, 360, 141, 41));
        toolButton_3->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_4 = new QToolButton(frame_5);
        toolButton_4->setObjectName("toolButton_4");
        toolButton_4->setGeometry(QRect(20, 420, 141, 41));
        toolButton_4->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_5 = new QToolButton(frame_5);
        toolButton_5->setObjectName("toolButton_5");
        toolButton_5->setGeometry(QRect(20, 180, 141, 41));
        toolButton_5->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        stackedWidget->addWidget(page_21);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1171, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "statistiques", nullptr));
        lblClients->setText(QCoreApplication::translate("MainWindow", "Liste des Clients", nullptr));
        btnListeClients_3->setText(QCoreApplication::translate("MainWindow", "Liste des clients", nullptr));
        btnAjouterClient_3->setText(QCoreApplication::translate("MainWindow", "Ajouter client", nullptr));
        lblListeClients->setText(QCoreApplication::translate("MainWindow", "Liste des Clients", nullptr));
        toolButton_6->setText(QCoreApplication::translate("MainWindow", "Fournisseurs", nullptr));
        toolButton_7->setText(QCoreApplication::translate("MainWindow", "Produis", nullptr));
        toolButton_8->setText(QCoreApplication::translate("MainWindow", "Personnels", nullptr));
        toolButton_9->setText(QCoreApplication::translate("MainWindow", "Locaux", nullptr));
        toolButton_10->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
        searchLineEdit->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color:#f5f6fa;border-radius:10px;padding:8px 16px;font-size:14px;", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher par ID ou Nom", nullptr));
        btnRechercher->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color:#a55eea;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:14px;", nullptr));
        btnRechercher->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        comboProfession->setItemText(0, QCoreApplication::translate("MainWindow", "Profession", nullptr));

        comboProfession->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color:#f5f6fa;border-radius:10px;padding:8px 16px;font-size:14px;", nullptr));
        btnFilter->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color:#a55eea;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:14px;", nullptr));
        btnFilter->setText(QCoreApplication::translate("MainWindow", "Filter", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableClients->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableClients->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableClients->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableClients->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\303\202ge", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableClients->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Statut de Fid\303\251lit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableClients->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Numero de telephone", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableClients->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "sexe", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableClients->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Actions", nullptr));
        btnExporter->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color:#2980b9;color:white;font-weight:bold;border-radius:15px;padding:8px 24px;font-size:15px;", nullptr));
        btnExporter->setText(QCoreApplication::translate("MainWindow", "Exporter", nullptr));
        toolButton_16->setText(QCoreApplication::translate("MainWindow", "Fournisseurs", nullptr));
        toolButton_17->setText(QCoreApplication::translate("MainWindow", "Produis", nullptr));
        toolButton_18->setText(QCoreApplication::translate("MainWindow", "Personnels", nullptr));
        toolButton_19->setText(QCoreApplication::translate("MainWindow", "Locaux", nullptr));
        toolButton_20->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
        lblFicheClient->setText(QCoreApplication::translate("MainWindow", "Fiche Client", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Telephone", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Sexe", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Date de naissance", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "statut de fidelit\303\251", nullptr));
        btnConfirmer->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color:#2980b9;color:white;font-weight:bold;border-radius:15px;padding:8px 24px;font-size:15px;", nullptr));
        btnConfirmer->setText(QCoreApplication::translate("MainWindow", "Confirmer", nullptr));
        btnAnnuler->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color:#636e72;color:white;font-weight:bold;border-radius:15px;padding:8px 24px;font-size:15px;", nullptr));
        btnAnnuler->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        lineEditNom->setText(QString());
        lineEditNom->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        lineEditPhone->setText(QString());
        lineEditPhone->setPlaceholderText(QCoreApplication::translate("MainWindow", "Phone Number", nullptr));
        checkNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        lineEditDateNaissance->setText(QString());
        lineEditDateNaissance->setPlaceholderText(QCoreApplication::translate("MainWindow", "Date de naissance", nullptr));
        lineEditID->setText(QString());
        lineEditID->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        lineEditPrenom->setText(QString());
        lineEditPrenom->setPlaceholderText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        checkOld->setText(QCoreApplication::translate("MainWindow", "Old", nullptr));
        checkVIP->setText(QCoreApplication::translate("MainWindow", "VIP", nullptr));
        comboSexe->setItemText(0, QCoreApplication::translate("MainWindow", "Homme", nullptr));
        comboSexe->setItemText(1, QCoreApplication::translate("MainWindow", "Femme", nullptr));

        comboSexe->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color:#41375f;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:15px;", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Ordonnance", nullptr));
        btnListeClients_2->setText(QCoreApplication::translate("MainWindow", "Liste des clients", nullptr));
        btnAjouterClient_2->setText(QCoreApplication::translate("MainWindow", "Ajouter client", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "Fournisseurs", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "Produis", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainWindow", "Personnels", nullptr));
        toolButton_4->setText(QCoreApplication::translate("MainWindow", "Locaux", nullptr));
        toolButton_5->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
