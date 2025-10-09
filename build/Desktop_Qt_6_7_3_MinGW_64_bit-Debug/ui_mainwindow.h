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
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *headerLayout;
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
    QPushButton *btnExporter;
    QHBoxLayout *headerLayout_2;
    QTableWidget *tablePersonnel;
    QHBoxLayout *actionButtonsLayout;
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
    QPushButton *btnListePersonnel_3;
    QPushButton *btnAjouterPersonnel_3;
    QLabel *label_16;
    QFrame *frame_2;
    QWidget *page_2;
    QWidget *page_21;
    QFrame *frameFicheClient;
    QLabel *lblFicheClient;
    QLabel *lblid;
    QLabel *lblnom;
    QLabel *lblprenom;
    QLabel *lbltel;
    QLabel *label_8;
    QLabel *lblbirth;
    QWidget *layoutWidget;
    QHBoxLayout *ajouterActionLayout;
    QPushButton *btnConfirmer;
    QPushButton *btnAnnuler;
    QLineEdit *lineEditNom;
    QLineEdit *lineEditPhone;
    QLineEdit *lineEditDateNaissance;
    QLineEdit *lineEditID;
    QLineEdit *lineEditPrenom;
    QComboBox *comboSexe;
    QLabel *lblnom_2;
    QLineEdit *lineEditNom_2;
    QPushButton *btnAjouterClient_2;
    QPushButton *btnListeClients_2;
    QFrame *frame_8;
    QToolButton *toolButton_fourn1_2;
    QToolButton *toolButton_prod1_2;
    QToolButton *toolButton_person1_2;
    QToolButton *toolButton_loc1_2;
    QToolButton *toolButton_client1_2;
    QLabel *label_5;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
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
        frame = new QFrame(page);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(210, 70, 961, 691));
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        headerLayout = new QHBoxLayout();
        headerLayout->setObjectName("headerLayout");

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
        searchLineEdit->setStyleSheet(QString::fromUtf8("background-color:#f5f6fa;border-radius:10px;padding:8px 16px;font-size:14px;color :black;"));

        searchLayout->addWidget(searchLineEdit);

        btnRechercher = new QPushButton(frame);
        btnRechercher->setObjectName("btnRechercher");

        searchLayout->addWidget(btnRechercher);

        comboProfession = new QComboBox(frame);
        comboProfession->addItem(QString());
        comboProfession->addItem(QString());
        comboProfession->addItem(QString());
        comboProfession->addItem(QString());
        comboProfession->addItem(QString());
        comboProfession->setObjectName("comboProfession");
        comboProfession->setAcceptDrops(false);
        comboProfession->setStyleSheet(QString::fromUtf8("background-color:#f5f6fa;border-radius:10px;padding:8px 16px;font-size:14px;color :black; "));
        comboProfession->setEditable(false);

        searchLayout->addWidget(comboProfession);

        btnFilter = new QPushButton(frame);
        btnFilter->setObjectName("btnFilter");
        btnFilter->setStyleSheet(QString::fromUtf8("background-color:#a55eea;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:14px;"));

        searchLayout->addWidget(btnFilter);

        btnExporter = new QPushButton(frame);
        btnExporter->setObjectName("btnExporter");
        btnExporter->setStyleSheet(QString::fromUtf8("background-color:#a55eea;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:14px;"));

        searchLayout->addWidget(btnExporter);


        verticalLayout->addLayout(searchLayout);

        headerLayout_2 = new QHBoxLayout();
        headerLayout_2->setObjectName("headerLayout_2");
        tablePersonnel = new QTableWidget(frame);
        if (tablePersonnel->columnCount() < 10)
            tablePersonnel->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tablePersonnel->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tablePersonnel->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tablePersonnel->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tablePersonnel->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tablePersonnel->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tablePersonnel->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tablePersonnel->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tablePersonnel->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tablePersonnel->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tablePersonnel->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        if (tablePersonnel->rowCount() < 8)
            tablePersonnel->setRowCount(8);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tablePersonnel->setItem(0, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tablePersonnel->setItem(0, 1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tablePersonnel->setItem(0, 2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tablePersonnel->setItem(0, 3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tablePersonnel->setItem(0, 9, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tablePersonnel->setItem(1, 0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tablePersonnel->setItem(1, 1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tablePersonnel->setItem(1, 2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tablePersonnel->setItem(1, 3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tablePersonnel->setItem(2, 0, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tablePersonnel->setItem(2, 1, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tablePersonnel->setItem(2, 2, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tablePersonnel->setItem(2, 3, __qtablewidgetitem22);
        tablePersonnel->setObjectName("tablePersonnel");
        tablePersonnel->setStyleSheet(QString::fromUtf8("/* --- Style du conteneur principal de la table --- */\n"
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

        headerLayout_2->addWidget(tablePersonnel);


        verticalLayout->addLayout(headerLayout_2);

        actionButtonsLayout = new QHBoxLayout();
        actionButtonsLayout->setObjectName("actionButtonsLayout");

        verticalLayout->addLayout(actionButtonsLayout);


        horizontalLayout->addLayout(verticalLayout);

        frame_6 = new QFrame(page);
        frame_6->setObjectName("frame_6");
        frame_6->setGeometry(QRect(0, 40, 191, 751));
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
        toolButton_fourn1->setGeometry(QRect(10, 290, 161, 41));
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
"font-size: 20px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_prod1 = new QToolButton(frame_6);
        toolButton_prod1->setObjectName("toolButton_prod1");
        toolButton_prod1->setGeometry(QRect(10, 350, 161, 41));
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
        toolButton_person1->setGeometry(QRect(10, 410, 161, 41));
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
"font-size: 20px;\n"
"    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #a29bfe, stop:1 #fd79a8);\n"
"}"));
        toolButton_loc1 = new QToolButton(frame_6);
        toolButton_loc1->setObjectName("toolButton_loc1");
        toolButton_loc1->setGeometry(QRect(10, 470, 161, 41));
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
        toolButton_client1->setGeometry(QRect(10, 230, 161, 41));
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
        label_4->setGeometry(QRect(10, 40, 161, 111));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/tt.png")));
        label_11 = new QLabel(frame_6);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(0, 230, 31, 41));
        label_11->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_11->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/client-removebg-preview.png")));
        label_12 = new QLabel(frame_6);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(0, 290, 31, 41));
        label_12->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_12->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/fournisseurs-removebg-preview.png")));
        label_13 = new QLabel(frame_6);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(0, 350, 31, 41));
        label_13->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/produit-removebg-preview.png")));
        label_14 = new QLabel(frame_6);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(0, 410, 31, 41));
        label_14->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_14->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/personal-removebg-preview.png")));
        label_15 = new QLabel(frame_6);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(0, 470, 31, 41));
        label_15->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_15->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/locaux-removebg-preview.png")));
        btnListePersonnel_3 = new QPushButton(page);
        btnListePersonnel_3->setObjectName("btnListePersonnel_3");
        btnListePersonnel_3->setGeometry(QRect(290, 10, 341, 41));
        btnListePersonnel_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        btnAjouterPersonnel_3 = new QPushButton(page);
        btnAjouterPersonnel_3->setObjectName("btnAjouterPersonnel_3");
        btnAjouterPersonnel_3->setGeometry(QRect(650, 10, 331, 41));
        btnAjouterPersonnel_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        label_16 = new QLabel(page);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(1220, 20, 211, 31));
        label_16->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 127);\n"
"border-color: rgb(0, 0, 255);"));
        label_16->setAlignment(Qt::AlignmentFlag::AlignCenter);
        frame_2 = new QFrame(page);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(1220, 50, 211, 711));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(186, 186, 186);"));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        page_21 = new QWidget();
        page_21->setObjectName("page_21");
        frameFicheClient = new QFrame(page_21);
        frameFicheClient->setObjectName("frameFicheClient");
        frameFicheClient->setGeometry(QRect(220, 80, 841, 641));
        frameFicheClient->setStyleSheet(QString::fromUtf8("border:2px solid #a55eea; border-radius:20px; background-color:#f5f6fa;\n"
"border-color: rgb(0, 0, 127);"));
        lblFicheClient = new QLabel(frameFicheClient);
        lblFicheClient->setObjectName("lblFicheClient");
        lblFicheClient->setGeometry(QRect(180, 70, 481, 68));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        lblFicheClient->setFont(font1);
        lblFicheClient->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 127);"));
        lblFicheClient->setFrameShape(QFrame::Shape::StyledPanel);
        lblFicheClient->setFrameShadow(QFrame::Shadow::Raised);
        lblFicheClient->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lblid = new QLabel(frameFicheClient);
        lblid->setObjectName("lblid");
        lblid->setGeometry(QRect(210, 180, 91, 20));
        lblid->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        lblnom = new QLabel(frameFicheClient);
        lblnom->setObjectName("lblnom");
        lblnom->setGeometry(QRect(210, 230, 91, 20));
        lblnom->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        lblprenom = new QLabel(frameFicheClient);
        lblprenom->setObjectName("lblprenom");
        lblprenom->setGeometry(QRect(210, 280, 91, 20));
        lblprenom->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        lbltel = new QLabel(frameFicheClient);
        lbltel->setObjectName("lbltel");
        lbltel->setGeometry(QRect(210, 380, 91, 20));
        lbltel->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        label_8 = new QLabel(frameFicheClient);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(210, 480, 91, 20));
        label_8->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        lblbirth = new QLabel(frameFicheClient);
        lblbirth->setObjectName("lblbirth");
        lblbirth->setGeometry(QRect(210, 430, 91, 21));
        lblbirth->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        layoutWidget = new QWidget(frameFicheClient);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(570, 550, 240, 42));
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
        lineEditNom->setGeometry(QRect(370, 230, 251, 26));
        lineEditNom->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEditPhone = new QLineEdit(frameFicheClient);
        lineEditPhone->setObjectName("lineEditPhone");
        lineEditPhone->setGeometry(QRect(370, 380, 251, 26));
        lineEditPhone->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEditDateNaissance = new QLineEdit(frameFicheClient);
        lineEditDateNaissance->setObjectName("lineEditDateNaissance");
        lineEditDateNaissance->setGeometry(QRect(370, 430, 251, 26));
        lineEditDateNaissance->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEditID = new QLineEdit(frameFicheClient);
        lineEditID->setObjectName("lineEditID");
        lineEditID->setGeometry(QRect(370, 180, 251, 26));
        lineEditID->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEditPrenom = new QLineEdit(frameFicheClient);
        lineEditPrenom->setObjectName("lineEditPrenom");
        lineEditPrenom->setGeometry(QRect(370, 280, 251, 26));
        lineEditPrenom->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        comboSexe = new QComboBox(frameFicheClient);
        comboSexe->addItem(QString());
        comboSexe->addItem(QString());
        comboSexe->setObjectName("comboSexe");
        comboSexe->setGeometry(QRect(370, 480, 251, 31));
        lblnom_2 = new QLabel(frameFicheClient);
        lblnom_2->setObjectName("lblnom_2");
        lblnom_2->setGeometry(QRect(210, 330, 91, 20));
        lblnom_2->setStyleSheet(QString::fromUtf8("background-color: rgb(48, 71, 120);"));
        lineEditNom_2 = new QLineEdit(frameFicheClient);
        lineEditNom_2->setObjectName("lineEditNom_2");
        lineEditNom_2->setGeometry(QRect(370, 330, 251, 26));
        lineEditNom_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        btnAjouterClient_2 = new QPushButton(page_21);
        btnAjouterClient_2->setObjectName("btnAjouterClient_2");
        btnAjouterClient_2->setGeometry(QRect(650, 10, 331, 41));
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
        btnListeClients_2 = new QPushButton(page_21);
        btnListeClients_2->setObjectName("btnListeClients_2");
        btnListeClients_2->setGeometry(QRect(290, 10, 341, 41));
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
        frame_8 = new QFrame(page_21);
        frame_8->setObjectName("frame_8");
        frame_8->setGeometry(QRect(0, 40, 191, 751));
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
        toolButton_fourn1_2 = new QToolButton(frame_8);
        toolButton_fourn1_2->setObjectName("toolButton_fourn1_2");
        toolButton_fourn1_2->setGeometry(QRect(10, 290, 161, 41));
        toolButton_fourn1_2->setStyleSheet(QString::fromUtf8("QToolButton {\n"
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
        toolButton_prod1_2 = new QToolButton(frame_8);
        toolButton_prod1_2->setObjectName("toolButton_prod1_2");
        toolButton_prod1_2->setGeometry(QRect(10, 350, 161, 41));
        toolButton_prod1_2->setStyleSheet(QString::fromUtf8("QToolButton {\n"
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
        toolButton_person1_2 = new QToolButton(frame_8);
        toolButton_person1_2->setObjectName("toolButton_person1_2");
        toolButton_person1_2->setGeometry(QRect(10, 410, 161, 41));
        toolButton_person1_2->setStyleSheet(QString::fromUtf8("QToolButton {\n"
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
        toolButton_loc1_2 = new QToolButton(frame_8);
        toolButton_loc1_2->setObjectName("toolButton_loc1_2");
        toolButton_loc1_2->setGeometry(QRect(10, 470, 161, 41));
        toolButton_loc1_2->setStyleSheet(QString::fromUtf8("QToolButton {\n"
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
        toolButton_client1_2 = new QToolButton(frame_8);
        toolButton_client1_2->setObjectName("toolButton_client1_2");
        toolButton_client1_2->setGeometry(QRect(10, 230, 161, 41));
        toolButton_client1_2->setStyleSheet(QString::fromUtf8("QToolButton {\n"
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
        label_5 = new QLabel(frame_8);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 40, 161, 111));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/tt.png")));
        label_17 = new QLabel(frame_8);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(0, 230, 31, 41));
        label_17->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_17->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/client-removebg-preview.png")));
        label_18 = new QLabel(frame_8);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(0, 290, 31, 41));
        label_18->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_18->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/fournisseurs-removebg-preview.png")));
        label_19 = new QLabel(frame_8);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(0, 350, 31, 41));
        label_19->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_19->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/produit-removebg-preview.png")));
        label_20 = new QLabel(frame_8);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(0, 410, 31, 41));
        label_20->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_20->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/personal-removebg-preview.png")));
        label_21 = new QLabel(frame_8);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(0, 470, 31, 41));
        label_21->setStyleSheet(QString::fromUtf8("background-color : #6c5ce7;"));
        label_21->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/locaux-removebg-preview.png")));
        stackedWidget->addWidget(page_21);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1499, 29));
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
        lblListeClients->setText(QCoreApplication::translate("MainWindow", "Liste du Personnel", nullptr));
        toolButton_6->setText(QCoreApplication::translate("MainWindow", "Fournisseurs", nullptr));
        toolButton_7->setText(QCoreApplication::translate("MainWindow", "Produis", nullptr));
        toolButton_8->setText(QCoreApplication::translate("MainWindow", "Personnels", nullptr));
        toolButton_9->setText(QCoreApplication::translate("MainWindow", "Locaux", nullptr));
        toolButton_10->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher par ID ou Nom", nullptr));
        btnRechercher->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color:#a55eea;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:14px;", nullptr));
        btnRechercher->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        comboProfession->setItemText(0, QCoreApplication::translate("MainWindow", "R\303\264les", nullptr));
        comboProfession->setItemText(1, QCoreApplication::translate("MainWindow", "Responsable", nullptr));
        comboProfession->setItemText(2, QCoreApplication::translate("MainWindow", "Vendeur", nullptr));
        comboProfession->setItemText(3, QCoreApplication::translate("MainWindow", "Manager", nullptr));
        comboProfession->setItemText(4, QCoreApplication::translate("MainWindow", "Opticien", nullptr));

        comboProfession->setCurrentText(QCoreApplication::translate("MainWindow", "R\303\264les", nullptr));
        btnFilter->setText(QCoreApplication::translate("MainWindow", "Filter", nullptr));
        btnExporter->setText(QCoreApplication::translate("MainWindow", "Exporter ", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tablePersonnel->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tablePersonnel->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tablePersonnel->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tablePersonnel->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Telephone", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tablePersonnel->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Mail", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tablePersonnel->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "R\303\264le", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tablePersonnel->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tablePersonnel->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Documents", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tablePersonnel->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Permissions", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tablePersonnel->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Actions", nullptr));

        const bool __sortingEnabled = tablePersonnel->isSortingEnabled();
        tablePersonnel->setSortingEnabled(false);
        tablePersonnel->setSortingEnabled(__sortingEnabled);

        toolButton_fourn1->setText(QCoreApplication::translate("MainWindow", "   Fournisseurs", nullptr));
        toolButton_prod1->setText(QCoreApplication::translate("MainWindow", "Produits", nullptr));
        toolButton_person1->setText(QCoreApplication::translate("MainWindow", "Personnel", nullptr));
        toolButton_loc1->setText(QCoreApplication::translate("MainWindow", "Locaux", nullptr));
        toolButton_client1->setText(QCoreApplication::translate("MainWindow", " Clients", nullptr));
        label_4->setText(QString());
        label_11->setText(QString());
        label_12->setText(QString());
        label_13->setText(QString());
        label_14->setText(QString());
        label_15->setText(QString());
        btnListePersonnel_3->setText(QCoreApplication::translate("MainWindow", "Liste du Personnel", nullptr));
        btnAjouterPersonnel_3->setText(QCoreApplication::translate("MainWindow", "Ajouter Personnel", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        lblFicheClient->setText(QCoreApplication::translate("MainWindow", "Fiche Personnel", nullptr));
        lblid->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        lblnom->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        lblprenom->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        lbltel->setText(QCoreApplication::translate("MainWindow", "Telephone", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Sexe", nullptr));
        lblbirth->setText(QCoreApplication::translate("MainWindow", "R\303\264le", nullptr));
        btnConfirmer->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color:#2980b9;color:white;font-weight:bold;border-radius:15px;padding:8px 24px;font-size:15px;", nullptr));
        btnConfirmer->setText(QCoreApplication::translate("MainWindow", "Confirmer", nullptr));
        btnAnnuler->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color:#636e72;color:white;font-weight:bold;border-radius:15px;padding:8px 24px;font-size:15px;", nullptr));
        btnAnnuler->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        lineEditNom->setText(QString());
        lineEditNom->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        lineEditPhone->setText(QString());
        lineEditPhone->setPlaceholderText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        lineEditDateNaissance->setText(QString());
        lineEditDateNaissance->setPlaceholderText(QCoreApplication::translate("MainWindow", "R\303\264le", nullptr));
        lineEditID->setText(QString());
        lineEditID->setPlaceholderText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        lineEditPrenom->setText(QString());
        lineEditPrenom->setPlaceholderText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        comboSexe->setItemText(0, QCoreApplication::translate("MainWindow", "Homme", nullptr));
        comboSexe->setItemText(1, QCoreApplication::translate("MainWindow", "Femme", nullptr));

        comboSexe->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color:#41375f;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:15px;", nullptr));
        lblnom_2->setText(QCoreApplication::translate("MainWindow", "Mail", nullptr));
        lineEditNom_2->setText(QString());
        lineEditNom_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "Mail", nullptr));
        btnAjouterClient_2->setText(QCoreApplication::translate("MainWindow", "Ajouter Personnel", nullptr));
        btnListeClients_2->setText(QCoreApplication::translate("MainWindow", "Liste du Personnel", nullptr));
        toolButton_fourn1_2->setText(QCoreApplication::translate("MainWindow", "  Fournisseurs", nullptr));
        toolButton_prod1_2->setText(QCoreApplication::translate("MainWindow", "Produits", nullptr));
        toolButton_person1_2->setText(QCoreApplication::translate("MainWindow", "Personnel", nullptr));
        toolButton_loc1_2->setText(QCoreApplication::translate("MainWindow", "Locaux", nullptr));
        toolButton_client1_2->setText(QCoreApplication::translate("MainWindow", " Clients", nullptr));
        label_5->setText(QString());
        label_17->setText(QString());
        label_18->setText(QString());
        label_19->setText(QString());
        label_20->setText(QString());
        label_21->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
