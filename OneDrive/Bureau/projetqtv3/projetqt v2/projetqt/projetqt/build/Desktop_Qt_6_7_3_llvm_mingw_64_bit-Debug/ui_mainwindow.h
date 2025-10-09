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
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
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
    QFrame *frame_6;
    QToolButton *toolButton_fourn1;
    QToolButton *toolButton_prod1;
    QToolButton *toolButton_person1;
    QToolButton *toolButton_loc1;
    QToolButton *toolButton_client1;
    QLabel *label_4;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_32;
    QPushButton *btnListePersonnel_5;
    QFrame *frame_18;
    QLabel *label_33;
    QLabel *label_34;
    QFrame *frame_12;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *headerLayout_9;
    QLabel *lblListeClients_5;
    QHBoxLayout *searchLayout_5;
    QFrame *frame_13;
    QToolButton *toolButton_27;
    QToolButton *toolButton_28;
    QToolButton *toolButton_29;
    QToolButton *toolButton_30;
    QToolButton *toolButton_31;
    QLineEdit *searchLineEdit_5;
    QPushButton *btnRechercher_5;
    QComboBox *comboProfession_5;
    QPushButton *btnFilter_5;
    QPushButton *btnExporter_5;
    QHBoxLayout *headerLayout_10;
    QTableWidget *tablePersonnel_3;
    QHBoxLayout *actionButtonsLayout_5;
    QPushButton *btnAjouterPersonnel_5;
    QWidget *page_2;
    QWidget *page_21;
    QFrame *frame_8;
    QToolButton *toolButton_fourn;
    QToolButton *toolButton_prod;
    QToolButton *toolButton_person;
    QToolButton *toolButton_loc;
    QToolButton *toolButton_client;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_29;
    QFrame *frameFicheClient_5;
    QLabel *lblFicheClient_5;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QWidget *layoutWidget_5;
    QHBoxLayout *ajouterActionLayout_5;
    QPushButton *btnAnnuler_5;
    QPushButton *btnConfirmer_5;
    QLineEdit *lineEditNom_6;
    QLineEdit *lineEditDateNaissance_6;
    QLineEdit *lineEditID_5;
    QLineEdit *lineEditPrenom_4;
    QLabel *label_27;
    QLabel *label_28;
    QLineEdit *lineEditDateNaissance_7;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QCalendarWidget *calendarWidget;
    QLabel *label_30;
    QDateEdit *dateEdit;
    QFrame *line;
    QComboBox *comboProfession_6;
    QLabel *label_35;
    QComboBox *comboProfession_7;
    QComboBox *comboProfession_8;
    QLabel *label_36;
    QPushButton *btnListeClients_8;
    QPushButton *btnAjouterClient_8;
    QFrame *frame_17;
    QLabel *label_31;
    QTableWidget *tableWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1499, 875);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 20, 1481, 811));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        page = new QWidget();
        page->setObjectName("page");
        frame_6 = new QFrame(page);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(10, 40, 181, 721));
        frame_6->setToolTipDuration(0);
        frame_6->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"    background-color: white;\n"
"    border-top-right-radius: 70px;   /* \360\237\221\210 arrondi seulement coin haut droit */\n"
"    border-top-left-radius: 0px;\n"
"    border-bottom-left-radius: 0px;\n"
"    border-bottom-right-radius: 0px;\n"
"\n"
"	\n"
"	background-color: rgb(0, 0, 124);\n"
"}\n"
""));
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);
        frame_6->setFrameShadow(QFrame::Shadow::Raised);
        toolButton_fourn1 = new QToolButton(frame_6);
        toolButton_fourn1->setObjectName("toolButton_fourn1");
        toolButton_fourn1->setGeometry(QRect(10, 240, 151, 41));
        toolButton_fourn1->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"font-size: 16px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_prod1 = new QToolButton(frame_6);
        toolButton_prod1->setObjectName("toolButton_prod1");
        toolButton_prod1->setGeometry(QRect(10, 300, 151, 41));
        toolButton_prod1->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"font-size: 20px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_person1 = new QToolButton(frame_6);
        toolButton_person1->setObjectName("toolButton_person1");
        toolButton_person1->setGeometry(QRect(10, 360, 151, 41));
        toolButton_person1->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"font-size: 17px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_loc1 = new QToolButton(frame_6);
        toolButton_loc1->setObjectName("toolButton_loc1");
        toolButton_loc1->setGeometry(QRect(10, 420, 151, 41));
        toolButton_loc1->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"font-size: 20px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_client1 = new QToolButton(frame_6);
        toolButton_client1->setObjectName("toolButton_client1");
        toolButton_client1->setGeometry(QRect(10, 180, 151, 41));
        toolButton_client1->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"font-size: 20px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        label_4 = new QLabel(frame_6);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 20, 161, 111));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/tt.png")));
        label_11 = new QLabel(frame_6);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(30, 180, 31, 41));
        label_11->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_11->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/client-removebg-preview.png")));
        label_12 = new QLabel(frame_6);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(30, 240, 31, 41));
        label_12->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_12->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/fournisseurs-removebg-preview.png")));
        label_13 = new QLabel(frame_6);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(30, 300, 31, 41));
        label_13->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/produit-removebg-preview.png")));
        label_14 = new QLabel(frame_6);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(30, 360, 31, 41));
        label_14->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_14->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/personal-removebg-preview.png")));
        label_15 = new QLabel(frame_6);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(30, 420, 31, 41));
        label_15->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_15->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/locaux-removebg-preview.png")));
        label_32 = new QLabel(page);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(1190, 0, 211, 31));
        label_32->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 127);\n"
"border-color: rgb(0, 0, 255);\n"
"font-size :20px;\n"
"border-top-right-radius: 20px;\n"
"border-top-left-radius: 20px;"));
        label_32->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btnListePersonnel_5 = new QPushButton(page);
        btnListePersonnel_5->setObjectName("btnListePersonnel_5");
        btnListePersonnel_5->setGeometry(QRect(270, 10, 341, 41));
        btnListePersonnel_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        frame_18 = new QFrame(page);
        frame_18->setObjectName("frame_18");
        frame_18->setGeometry(QRect(1190, 30, 211, 711));
        frame_18->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 186, 186);"));
        frame_18->setFrameShape(QFrame::Shape::StyledPanel);
        frame_18->setFrameShadow(QFrame::Shadow::Raised);
        label_33 = new QLabel(frame_18);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(10, -20, 191, 351));
        label_33->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/784a706a-f6af-4062-9180-299d6847a0c1.png")));
        label_33->setScaledContents(true);
        label_33->setWordWrap(false);
        label_33->setOpenExternalLinks(true);
        label_34 = new QLabel(frame_18);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(10, 340, 191, 351));
        label_34->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/456.png")));
        label_34->setScaledContents(true);
        label_34->setWordWrap(true);
        label_34->setOpenExternalLinks(true);
        frame_12 = new QFrame(page);
        frame_12->setObjectName("frame_12");
        frame_12->setGeometry(QRect(210, 70, 961, 691));
        frame_12->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        frame_12->setFrameShape(QFrame::Shape::StyledPanel);
        frame_12->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_12);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        headerLayout_9 = new QHBoxLayout();
        headerLayout_9->setObjectName("headerLayout_9");

        verticalLayout_5->addLayout(headerLayout_9);

        lblListeClients_5 = new QLabel(frame_12);
        lblListeClients_5->setObjectName("lblListeClients_5");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        lblListeClients_5->setFont(font);
        lblListeClients_5->setStyleSheet(QString::fromUtf8("color:#2d224c;font-weight:bold;margin:16px 0 8px 0;\n"
"background-color: rgb(255, 255, 255);"));

        verticalLayout_5->addWidget(lblListeClients_5);

        searchLayout_5 = new QHBoxLayout();
        searchLayout_5->setObjectName("searchLayout_5");
        frame_13 = new QFrame(frame_12);
        frame_13->setObjectName("frame_13");
        frame_13->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 124);; border-radius:20px;"));
        frame_13->setFrameShape(QFrame::Shape::StyledPanel);
        frame_13->setFrameShadow(QFrame::Shadow::Raised);
        toolButton_27 = new QToolButton(frame_13);
        toolButton_27->setObjectName("toolButton_27");
        toolButton_27->setGeometry(QRect(20, 240, 141, 41));
        toolButton_27->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC); }"));
        toolButton_28 = new QToolButton(frame_13);
        toolButton_28->setObjectName("toolButton_28");
        toolButton_28->setGeometry(QRect(20, 300, 141, 41));
        toolButton_28->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC); }"));
        toolButton_29 = new QToolButton(frame_13);
        toolButton_29->setObjectName("toolButton_29");
        toolButton_29->setGeometry(QRect(20, 360, 141, 41));
        toolButton_29->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC); }"));
        toolButton_30 = new QToolButton(frame_13);
        toolButton_30->setObjectName("toolButton_30");
        toolButton_30->setGeometry(QRect(20, 420, 141, 41));
        toolButton_30->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC); }"));
        toolButton_31 = new QToolButton(frame_13);
        toolButton_31->setObjectName("toolButton_31");
        toolButton_31->setGeometry(QRect(20, 180, 141, 41));
        toolButton_31->setStyleSheet(QString::fromUtf8("QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7); } QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC); }\n"
""));

        searchLayout_5->addWidget(frame_13);

        searchLineEdit_5 = new QLineEdit(frame_12);
        searchLineEdit_5->setObjectName("searchLineEdit_5");
        searchLineEdit_5->setStyleSheet(QString::fromUtf8("background-color:#f5f6fa;border-radius:10px;padding:8px 16px;font-size:14px;color :black;"));

        searchLayout_5->addWidget(searchLineEdit_5);

        btnRechercher_5 = new QPushButton(frame_12);
        btnRechercher_5->setObjectName("btnRechercher_5");

        searchLayout_5->addWidget(btnRechercher_5);

        comboProfession_5 = new QComboBox(frame_12);
        comboProfession_5->addItem(QString());
        comboProfession_5->addItem(QString());
        comboProfession_5->addItem(QString());
        comboProfession_5->addItem(QString());
        comboProfession_5->addItem(QString());
        comboProfession_5->setObjectName("comboProfession_5");
        comboProfession_5->setAcceptDrops(false);
        comboProfession_5->setStyleSheet(QString::fromUtf8("background-color:#f5f6fa;border-radius:10px;padding:8px 16px;font-size:14px;color :black; "));
        comboProfession_5->setEditable(false);

        searchLayout_5->addWidget(comboProfession_5);

        btnFilter_5 = new QPushButton(frame_12);
        btnFilter_5->setObjectName("btnFilter_5");
        btnFilter_5->setStyleSheet(QString::fromUtf8("background-color:#a55eea;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:14px;"));

        searchLayout_5->addWidget(btnFilter_5);

        btnExporter_5 = new QPushButton(frame_12);
        btnExporter_5->setObjectName("btnExporter_5");
        btnExporter_5->setStyleSheet(QString::fromUtf8("background-color:#a55eea;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:14px;"));

        searchLayout_5->addWidget(btnExporter_5);


        verticalLayout_5->addLayout(searchLayout_5);

        headerLayout_10 = new QHBoxLayout();
        headerLayout_10->setObjectName("headerLayout_10");
        tablePersonnel_3 = new QTableWidget(frame_12);
        if (tablePersonnel_3->columnCount() < 11)
            tablePersonnel_3->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tablePersonnel_3->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tablePersonnel_3->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tablePersonnel_3->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tablePersonnel_3->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tablePersonnel_3->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tablePersonnel_3->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tablePersonnel_3->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tablePersonnel_3->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tablePersonnel_3->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tablePersonnel_3->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tablePersonnel_3->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        if (tablePersonnel_3->rowCount() < 8)
            tablePersonnel_3->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tablePersonnel_3->setItem(0, 0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tablePersonnel_3->setItem(0, 1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tablePersonnel_3->setItem(0, 2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tablePersonnel_3->setItem(0, 3, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tablePersonnel_3->setItem(0, 10, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tablePersonnel_3->setItem(1, 0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tablePersonnel_3->setItem(1, 1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tablePersonnel_3->setItem(1, 2, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tablePersonnel_3->setItem(1, 3, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tablePersonnel_3->setItem(2, 0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tablePersonnel_3->setItem(2, 1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tablePersonnel_3->setItem(2, 2, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tablePersonnel_3->setItem(2, 3, __qtablewidgetitem23);
        tablePersonnel_3->setObjectName("tablePersonnel_3");
        tablePersonnel_3->setStyleSheet(QString::fromUtf8("/* --- Style du conteneur principal de la table --- */\n"
"QTableWidget {\n"
"    background-color: white;\n"
"    color: rgb(0, 0, 0);\n"
"    border-radius: 10px;\n"
"    gridline-color: #dfe6e9;\n"
"    border: 1px solid #dfe6e9;\n"
"}\n"
"\n"
"/* --- Style de l'en-t\303\252te --- */\n"
"QHeaderView::section {\n"
"    background-color: #2d224c;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    padding: 8px;\n"
"    border: none;\n"
"}\n"
"\n"
"/* --- Style pour chaque cellule (SANS PADDING) --- */\n"
"QTableWidget::item {\n"
"    border-bottom: 1px solid #dfe6e9;\n"
"}\n"
"\n"
"/* --- Style pour les cellules s\303\251lectionn\303\251es --- */\n"
"QTableWidget::item:selected {\n"
"    background-color: #a29bfe;\n"
"    color: white;\n"
"}"));

        headerLayout_10->addWidget(tablePersonnel_3);


        verticalLayout_5->addLayout(headerLayout_10);

        actionButtonsLayout_5 = new QHBoxLayout();
        actionButtonsLayout_5->setObjectName("actionButtonsLayout_5");

        verticalLayout_5->addLayout(actionButtonsLayout_5);


        horizontalLayout_5->addLayout(verticalLayout_5);

        btnAjouterPersonnel_5 = new QPushButton(page);
        btnAjouterPersonnel_5->setObjectName("btnAjouterPersonnel_5");
        btnAjouterPersonnel_5->setGeometry(QRect(640, 10, 331, 41));
        btnAjouterPersonnel_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        page_21 = new QWidget();
        page_21->setObjectName("page_21");
        frame_8 = new QFrame(page_21);
        frame_8->setObjectName("frame_8");
        frame_8->setGeometry(QRect(10, 40, 181, 721));
        frame_8->setToolTipDuration(0);
        frame_8->setStyleSheet(QString::fromUtf8("QFrame {\n"
"    border: none;\n"
"    background-color: white;\n"
"    border-top-right-radius: 70px;   /* \360\237\221\210 arrondi seulement coin haut droit */\n"
"    border-top-left-radius: 0px;\n"
"    border-bottom-left-radius: 0px;\n"
"    border-bottom-right-radius: 0px;\n"
"\n"
"	\n"
"	background-color: rgb(0, 0, 124);\n"
"}\n"
""));
        frame_8->setFrameShape(QFrame::Shape::StyledPanel);
        frame_8->setFrameShadow(QFrame::Shadow::Raised);
        toolButton_fourn = new QToolButton(frame_8);
        toolButton_fourn->setObjectName("toolButton_fourn");
        toolButton_fourn->setGeometry(QRect(10, 240, 151, 41));
        toolButton_fourn->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"font-size: 20px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_prod = new QToolButton(frame_8);
        toolButton_prod->setObjectName("toolButton_prod");
        toolButton_prod->setGeometry(QRect(10, 300, 151, 41));
        toolButton_prod->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"font-size: 20px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_person = new QToolButton(frame_8);
        toolButton_person->setObjectName("toolButton_person");
        toolButton_person->setGeometry(QRect(10, 360, 151, 41));
        toolButton_person->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"font-size: 20px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_loc = new QToolButton(frame_8);
        toolButton_loc->setObjectName("toolButton_loc");
        toolButton_loc->setGeometry(QRect(10, 420, 151, 41));
        toolButton_loc->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"font-size: 20px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_client = new QToolButton(frame_8);
        toolButton_client->setObjectName("toolButton_client");
        toolButton_client->setGeometry(QRect(10, 180, 151, 41));
        toolButton_client->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QToolButton:hover {\n"
"font-size: 20px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        label_18 = new QLabel(frame_8);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(10, 20, 161, 111));
        label_18->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/tt.png")));
        label_19 = new QLabel(frame_8);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(30, 180, 31, 41));
        label_19->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_19->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/client-removebg-preview.png")));
        label_20 = new QLabel(frame_8);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(30, 240, 31, 41));
        label_20->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_20->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/fournisseurs-removebg-preview.png")));
        label_21 = new QLabel(frame_8);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(30, 300, 31, 41));
        label_21->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_21->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/produit-removebg-preview.png")));
        label_22 = new QLabel(frame_8);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(30, 360, 31, 41));
        label_22->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_22->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/personal-removebg-preview.png")));
        label_23 = new QLabel(frame_8);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(30, 420, 31, 41));
        label_23->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_23->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/locaux-removebg-preview.png")));
        label_29 = new QLabel(page_21);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(1210, 40, 211, 31));
        label_29->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 0, 0);\n"
"border-color: rgb(0, 0, 255);\n"
"font-size :20px;\n"
"border-top-right-radius: 20px;\n"
"border-top-left-radius: 20px;"));
        label_29->setAlignment(Qt::AlignmentFlag::AlignCenter);
        frameFicheClient_5 = new QFrame(page_21);
        frameFicheClient_5->setObjectName("frameFicheClient_5");
        frameFicheClient_5->setGeometry(QRect(200, 120, 951, 541));
        frameFicheClient_5->setStyleSheet(QString::fromUtf8("border:2px solid #a55eea; border-radius:20px; background-color:#f5f6fa;\n"
"border-color: rgb(0, 0, 127);"));
        lblFicheClient_5 = new QLabel(frameFicheClient_5);
        lblFicheClient_5->setObjectName("lblFicheClient_5");
        lblFicheClient_5->setGeometry(QRect(370, 10, 211, 68));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        lblFicheClient_5->setFont(font1);
        lblFicheClient_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 127);"));
        lblFicheClient_5->setFrameShape(QFrame::Shape::StyledPanel);
        lblFicheClient_5->setFrameShadow(QFrame::Shadow::Raised);
        label_5 = new QLabel(frameFicheClient_5);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(100, 90, 91, 20));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        label_6 = new QLabel(frameFicheClient_5);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(100, 130, 91, 20));
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        label_7 = new QLabel(frameFicheClient_5);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(100, 170, 91, 20));
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        label_24 = new QLabel(frameFicheClient_5);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(100, 210, 91, 20));
        label_24->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        label_25 = new QLabel(frameFicheClient_5);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(100, 290, 91, 20));
        label_25->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        label_26 = new QLabel(frameFicheClient_5);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(100, 250, 91, 21));
        label_26->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        layoutWidget_5 = new QWidget(frameFicheClient_5);
        layoutWidget_5->setObjectName("layoutWidget_5");
        layoutWidget_5->setGeometry(QRect(670, 470, 240, 45));
        ajouterActionLayout_5 = new QHBoxLayout(layoutWidget_5);
        ajouterActionLayout_5->setObjectName("ajouterActionLayout_5");
        ajouterActionLayout_5->setContentsMargins(0, 0, 0, 0);
        btnAnnuler_5 = new QPushButton(layoutWidget_5);
        btnAnnuler_5->setObjectName("btnAnnuler_5");
        btnAnnuler_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton:hover {\n"
"font-size: 20px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));

        ajouterActionLayout_5->addWidget(btnAnnuler_5);

        btnConfirmer_5 = new QPushButton(layoutWidget_5);
        btnConfirmer_5->setObjectName("btnConfirmer_5");
        btnConfirmer_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    color: white;\n"
"    padding: 12px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #6c5ce7, stop:1 #a29bfe);\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton:hover {\n"
"font-size: 20px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));

        ajouterActionLayout_5->addWidget(btnConfirmer_5);

        lineEditNom_6 = new QLineEdit(frameFicheClient_5);
        lineEditNom_6->setObjectName("lineEditNom_6");
        lineEditNom_6->setGeometry(QRect(220, 130, 251, 26));
        lineEditNom_6->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEditDateNaissance_6 = new QLineEdit(frameFicheClient_5);
        lineEditDateNaissance_6->setObjectName("lineEditDateNaissance_6");
        lineEditDateNaissance_6->setGeometry(QRect(220, 250, 251, 26));
        lineEditDateNaissance_6->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEditID_5 = new QLineEdit(frameFicheClient_5);
        lineEditID_5->setObjectName("lineEditID_5");
        lineEditID_5->setGeometry(QRect(220, 90, 251, 26));
        lineEditID_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEditPrenom_4 = new QLineEdit(frameFicheClient_5);
        lineEditPrenom_4->setObjectName("lineEditPrenom_4");
        lineEditPrenom_4->setGeometry(QRect(220, 170, 251, 26));
        lineEditPrenom_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_27 = new QLabel(frameFicheClient_5);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(100, 330, 91, 20));
        label_27->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        label_28 = new QLabel(frameFicheClient_5);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(100, 370, 91, 20));
        label_28->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        lineEditDateNaissance_7 = new QLineEdit(frameFicheClient_5);
        lineEditDateNaissance_7->setObjectName("lineEditDateNaissance_7");
        lineEditDateNaissance_7->setGeometry(QRect(220, 290, 251, 26));
        lineEditDateNaissance_7->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        spinBox = new QSpinBox(frameFicheClient_5);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(220, 370, 141, 25));
        spinBox->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        spinBox->setStepType(QAbstractSpinBox::StepType::AdaptiveDecimalStepType);
        spinBox_2 = new QSpinBox(frameFicheClient_5);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setGeometry(QRect(220, 330, 141, 25));
        spinBox_2->setStyleSheet(QString::fromUtf8("color :black;"));
        calendarWidget = new QCalendarWidget(frameFicheClient_5);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(550, 200, 256, 163));
        calendarWidget->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_30 = new QLabel(frameFicheClient_5);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(550, 160, 91, 20));
        label_30->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        dateEdit = new QDateEdit(frameFicheClient_5);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(660, 160, 110, 25));
        dateEdit->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        line = new QFrame(frameFicheClient_5);
        line->setObjectName("line");
        line->setGeometry(QRect(500, 80, 20, 371));
        line->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        comboProfession_6 = new QComboBox(frameFicheClient_5);
        comboProfession_6->addItem(QString());
        comboProfession_6->addItem(QString());
        comboProfession_6->addItem(QString());
        comboProfession_6->addItem(QString());
        comboProfession_6->addItem(QString());
        comboProfession_6->addItem(QString());
        comboProfession_6->setObjectName("comboProfession_6");
        comboProfession_6->setGeometry(QRect(220, 200, 91, 41));
        comboProfession_6->setStyleSheet(QString::fromUtf8("background-color:#41375f;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:15px;"));
        comboProfession_6->setEditable(false);
        label_35 = new QLabel(frameFicheClient_5);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(100, 410, 91, 20));
        label_35->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        comboProfession_7 = new QComboBox(frameFicheClient_5);
        comboProfession_7->addItem(QString());
        comboProfession_7->addItem(QString());
        comboProfession_7->addItem(QString());
        comboProfession_7->addItem(QString());
        comboProfession_7->setObjectName("comboProfession_7");
        comboProfession_7->setGeometry(QRect(220, 400, 121, 41));
        comboProfession_7->setStyleSheet(QString::fromUtf8("background-color:#41375f;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:15px;"));
        comboProfession_7->setEditable(false);
        comboProfession_8 = new QComboBox(frameFicheClient_5);
        comboProfession_8->addItem(QString());
        comboProfession_8->addItem(QString());
        comboProfession_8->addItem(QString());
        comboProfession_8->addItem(QString());
        comboProfession_8->setObjectName("comboProfession_8");
        comboProfession_8->setGeometry(QRect(670, 100, 121, 41));
        comboProfession_8->setStyleSheet(QString::fromUtf8("background-color:#41375f;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:15px;"));
        comboProfession_8->setEditable(false);
        label_36 = new QLabel(frameFicheClient_5);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(550, 110, 91, 20));
        label_36->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        btnListeClients_8 = new QPushButton(page_21);
        btnListeClients_8->setObjectName("btnListeClients_8");
        btnListeClients_8->setGeometry(QRect(240, 40, 341, 41));
        btnListeClients_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        btnAjouterClient_8 = new QPushButton(page_21);
        btnAjouterClient_8->setObjectName("btnAjouterClient_8");
        btnAjouterClient_8->setGeometry(QRect(620, 40, 331, 41));
        btnAjouterClient_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        frame_17 = new QFrame(page_21);
        frame_17->setObjectName("frame_17");
        frame_17->setGeometry(QRect(1210, 70, 211, 631));
        frame_17->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 186, 186);\n"
"border-bottom-right-radius: 25px;\n"
"border-bottom-left-radius: 25px;"));
        frame_17->setFrameShape(QFrame::Shape::StyledPanel);
        frame_17->setFrameShadow(QFrame::Shadow::Raised);
        label_31 = new QLabel(frame_17);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(10, 100, 191, 201));
        label_31->setAutoFillBackground(false);
        label_31->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/fd6699_5ad46a373a2e4385bddfb0c531358041~mv2.png")));
        label_31->setScaledContents(true);
        tableWidget = new QTableWidget(frame_17);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem24);
        if (tableWidget->rowCount() < 5)
            tableWidget->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setItem(3, 0, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget->setItem(4, 0, __qtablewidgetitem29);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(40, 340, 131, 181));
        tableWidget->setStyleSheet(QString::fromUtf8("/* --- Style du conteneur principal de la table --- */\n"
"QTableWidget {\n"
"    background-color: white;\n"
"    color: rgb(0, 0, 0);\n"
"    border-radius: 10px;\n"
"    gridline-color: #dfe6e9;\n"
"    border: 1px solid #dfe6e9;\n"
"}\n"
"\n"
"/* --- Style de l'en-t\303\252te --- */\n"
"QHeaderView::section {\n"
"    background-color: #2d224c;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    padding: 8px;\n"
"    border: none;\n"
"}\n"
"\n"
"/* --- Style pour chaque cellule (SANS PADDING) --- */\n"
"QTableWidget::item {\n"
"    border-bottom: 1px solid #dfe6e9;\n"
"}\n"
"\n"
"/* --- Style pour les cellules s\303\251lectionn\303\251es --- */\n"
"QTableWidget::item:selected {\n"
"    background-color: #a29bfe;\n"
"    color: white;\n"
"}"));
        stackedWidget->addWidget(page_21);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1499, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        toolButton_fourn1->setText(QCoreApplication::translate("MainWindow", "        Fournisseurs", nullptr));
        toolButton_prod1->setText(QCoreApplication::translate("MainWindow", "      Produis", nullptr));
        toolButton_person1->setText(QCoreApplication::translate("MainWindow", "           Personnels", nullptr));
        toolButton_loc1->setText(QCoreApplication::translate("MainWindow", "      Locaux", nullptr));
        toolButton_client1->setText(QCoreApplication::translate("MainWindow", "    Client", nullptr));
        label_4->setText(QString());
        label_11->setText(QString());
        label_12->setText(QString());
        label_13->setText(QString());
        label_14->setText(QString());
        label_15->setText(QString());
        label_32->setText(QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        btnListePersonnel_5->setText(QCoreApplication::translate("MainWindow", "Liste du Produit", nullptr));
        label_33->setText(QString());
        label_34->setText(QString());
        lblListeClients_5->setText(QCoreApplication::translate("MainWindow", "Liste du Liste du Produit", nullptr));
        toolButton_27->setText(QCoreApplication::translate("MainWindow", "Fournisseurs", nullptr));
        toolButton_28->setText(QCoreApplication::translate("MainWindow", "Produis", nullptr));
        toolButton_29->setText(QCoreApplication::translate("MainWindow", "Personnels", nullptr));
        toolButton_30->setText(QCoreApplication::translate("MainWindow", "Locaux", nullptr));
        toolButton_31->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
        searchLineEdit_5->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher par ID ou Nom de Produit", nullptr));
        btnRechercher_5->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color:#a55eea;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:14px;", nullptr));
        btnRechercher_5->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        comboProfession_5->setItemText(0, QCoreApplication::translate("MainWindow", "Trie", nullptr));
        comboProfession_5->setItemText(1, QCoreApplication::translate("MainWindow", "Prix Bas", nullptr));
        comboProfession_5->setItemText(2, QCoreApplication::translate("MainWindow", "Prix Haut", nullptr));
        comboProfession_5->setItemText(3, QCoreApplication::translate("MainWindow", "A-Z", nullptr));
        comboProfession_5->setItemText(4, QCoreApplication::translate("MainWindow", "Z-A", nullptr));

        comboProfession_5->setCurrentText(QCoreApplication::translate("MainWindow", "Trie", nullptr));
        btnFilter_5->setText(QCoreApplication::translate("MainWindow", "Filter", nullptr));
        btnExporter_5->setText(QCoreApplication::translate("MainWindow", "Exporter ", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tablePersonnel_3->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID Produit", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tablePersonnel_3->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Marque", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tablePersonnel_3->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Mod\303\251le", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tablePersonnel_3->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tablePersonnel_3->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Couleur", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tablePersonnel_3->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Prix", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tablePersonnel_3->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tablePersonnel_3->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Mati\303\250re", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tablePersonnel_3->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Genre", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tablePersonnel_3->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Date d'ajout", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tablePersonnel_3->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Actions", nullptr));

        const bool __sortingEnabled = tablePersonnel_3->isSortingEnabled();
        tablePersonnel_3->setSortingEnabled(false);
        tablePersonnel_3->setSortingEnabled(__sortingEnabled);

        btnAjouterPersonnel_5->setText(QCoreApplication::translate("MainWindow", "Ajouter Produit", nullptr));
        toolButton_fourn->setText(QCoreApplication::translate("MainWindow", "        Fournisseurs", nullptr));
        toolButton_prod->setText(QCoreApplication::translate("MainWindow", "      Produis", nullptr));
        toolButton_person->setText(QCoreApplication::translate("MainWindow", "           Personnels", nullptr));
        toolButton_loc->setText(QCoreApplication::translate("MainWindow", "      Locaux", nullptr));
        toolButton_client->setText(QCoreApplication::translate("MainWindow", "    Client", nullptr));
        label_18->setText(QString());
        label_19->setText(QString());
        label_20->setText(QString());
        label_21->setText(QString());
        label_22->setText(QString());
        label_23->setText(QString());
        label_29->setText(QCoreApplication::translate("MainWindow", "alerte", nullptr));
        lblFicheClient_5->setText(QCoreApplication::translate("MainWindow", "Fiche Produit", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "ID Produit", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Marque", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Mod\303\250le", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "Prix public", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "Couleur", nullptr));
        btnAnnuler_5->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        btnConfirmer_5->setText(QCoreApplication::translate("MainWindow", "Confirmer", nullptr));
        lineEditNom_6->setText(QString());
        lineEditNom_6->setPlaceholderText(QCoreApplication::translate("MainWindow", "Marque", nullptr));
        lineEditDateNaissance_6->setText(QString());
        lineEditDateNaissance_6->setPlaceholderText(QCoreApplication::translate("MainWindow", "Couleur", nullptr));
        lineEditID_5->setText(QString());
        lineEditID_5->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID Produit", nullptr));
        lineEditPrenom_4->setText(QString());
        lineEditPrenom_4->setPlaceholderText(QCoreApplication::translate("MainWindow", "Mod\303\250le", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "Remise", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "Quantit\303\251", nullptr));
        lineEditDateNaissance_7->setText(QString());
        lineEditDateNaissance_7->setPlaceholderText(QCoreApplication::translate("MainWindow", "Prix public", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "Date d'ajout", nullptr));
        comboProfession_6->setItemText(0, QCoreApplication::translate("MainWindow", "Type", nullptr));
        comboProfession_6->setItemText(1, QCoreApplication::translate("MainWindow", "Solaire", nullptr));
        comboProfession_6->setItemText(2, QCoreApplication::translate("MainWindow", "Vue", nullptr));
        comboProfession_6->setItemText(3, QCoreApplication::translate("MainWindow", "Mixte", nullptr));
        comboProfession_6->setItemText(4, QCoreApplication::translate("MainWindow", "Lentille", nullptr));
        comboProfession_6->setItemText(5, QString());

        label_35->setText(QCoreApplication::translate("MainWindow", "Mati\303\250re", nullptr));
        comboProfession_7->setItemText(0, QCoreApplication::translate("MainWindow", "Choisir", nullptr));
        comboProfession_7->setItemText(1, QCoreApplication::translate("MainWindow", "plastique", nullptr));
        comboProfession_7->setItemText(2, QCoreApplication::translate("MainWindow", "m\303\251tal", nullptr));
        comboProfession_7->setItemText(3, QCoreApplication::translate("MainWindow", "titane", nullptr));

        comboProfession_8->setItemText(0, QCoreApplication::translate("MainWindow", "Choisir", nullptr));
        comboProfession_8->setItemText(1, QCoreApplication::translate("MainWindow", "Homme", nullptr));
        comboProfession_8->setItemText(2, QCoreApplication::translate("MainWindow", "Femme", nullptr));
        comboProfession_8->setItemText(3, QCoreApplication::translate("MainWindow", "Unisexe", nullptr));

        label_36->setText(QCoreApplication::translate("MainWindow", "Genre", nullptr));
        btnListeClients_8->setText(QCoreApplication::translate("MainWindow", "Liste du Produit", nullptr));
        btnAjouterClient_8->setText(QCoreApplication::translate("MainWindow", "Ajouter Produit", nullptr));
        label_31->setText(QString());
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "ID Produit", nullptr));

        const bool __sortingEnabled1 = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->item(0, 0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "2312", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->item(1, 0);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "6574", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->item(2, 0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "7456", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->item(3, 0);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "0879", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(4, 0);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "2313", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled1);

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
