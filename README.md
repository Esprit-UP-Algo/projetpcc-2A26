<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>MainWindow</class>
 <widget class="QMainWindow" name="MainWindow">
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>1171</width>
    <height>719</height>
   </rect>
  </property>
  <property name="windowTitle">
   <string>MainWindow</string>
  </property>
  <widget class="QWidget" name="centralwidget">
   <widget class="QStackedWidget" name="stackedWidget">
    <property name="geometry">
     <rect>
      <x>20</x>
      <y>30</y>
      <width>1141</width>
      <height>621</height>
     </rect>
    </property>
    <property name="currentIndex">
     <number>0</number>
    </property>
    <widget class="QWidget" name="page">
     <widget class="QFrame" name="frame">
      <property name="geometry">
       <rect>
        <x>-30</x>
        <y>-10</y>
        <width>961</width>
        <height>601</height>
       </rect>
      </property>
      <property name="styleSheet">
       <string notr="true"/>
      </property>
      <property name="frameShape">
       <enum>QFrame::Shape::StyledPanel</enum>
      </property>
      <property name="frameShadow">
       <enum>QFrame::Shadow::Raised</enum>
      </property>
      <widget class="QFrame" name="frame_3">
       <property name="geometry">
        <rect>
         <x>30</x>
         <y>30</y>
         <width>161</width>
         <height>541</height>
        </rect>
       </property>
       <property name="styleSheet">
        <string notr="true">background-color: rgb(0, 0, 124);</string>
       </property>
       <property name="frameShape">
        <enum>QFrame::Shape::StyledPanel</enum>
       </property>
       <property name="frameShadow">
        <enum>QFrame::Shadow::Raised</enum>
       </property>
       <widget class="QToolButton" name="toolButton_4">
        <property name="geometry">
         <rect>
          <x>0</x>
          <y>180</y>
          <width>171</width>
          <height>51</height>
         </rect>
        </property>
        <property name="styleSheet">
         <string notr="true">QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7);
border-top-right-radius: 0px;   /* 👈 arrondi seulement coin haut droit */
    border-top-left-radius: 20px;
    border-bottom-left-radius: 20px;
    border-bottom-right-radius: 0px ;
	 font-size: 20px;
 } 
QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);
font-size: 25px; }
</string>
        </property>
        <property name="text">
         <string>Fournisseur</string>
        </property>
       </widget>
       <widget class="QToolButton" name="toolButton_5">
        <property name="geometry">
         <rect>
          <x>0</x>
          <y>250</y>
          <width>191</width>
          <height>51</height>
         </rect>
        </property>
        <property name="styleSheet">
         <string notr="true">QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7);
border-top-right-radius: 0px;   /* 👈 arrondi seulement coin haut droit */
    border-top-left-radius: 20px;
    border-bottom-left-radius: 20px;
    border-bottom-right-radius: 0px ;
	 font-size: 20px;
 } 
QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);
font-size: 25px; }
</string>
        </property>
        <property name="text">
         <string>Client</string>
        </property>
       </widget>
       <widget class="QToolButton" name="toolButton">
        <property name="geometry">
         <rect>
          <x>0</x>
          <y>330</y>
          <width>191</width>
          <height>51</height>
         </rect>
        </property>
        <property name="styleSheet">
         <string notr="true">QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7);
border-top-right-radius: 0px;   /* 👈 arrondi seulement coin haut droit */
    border-top-left-radius: 20px;
    border-bottom-left-radius: 20px;
    border-bottom-right-radius: 0px ;
	 font-size: 20px;
 } 
QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);
font-size: 25px; }
</string>
        </property>
        <property name="text">
         <string>Produit</string>
        </property>
       </widget>
       <widget class="QToolButton" name="toolButton_2">
        <property name="geometry">
         <rect>
          <x>0</x>
          <y>390</y>
          <width>191</width>
          <height>51</height>
         </rect>
        </property>
        <property name="styleSheet">
         <string notr="true">QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7);
border-top-right-radius: 0px;   /* 👈 arrondi seulement coin haut droit */
    border-top-left-radius: 20px;
    border-bottom-left-radius: 20px;
    border-bottom-right-radius: 0px ;
	 font-size: 20px;
 } 
QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);
font-size: 25px; }
</string>
        </property>
        <property name="text">
         <string>Personnel</string>
        </property>
       </widget>
       <widget class="QToolButton" name="toolButton_6">
        <property name="geometry">
         <rect>
          <x>0</x>
          <y>460</y>
          <width>191</width>
          <height>51</height>
         </rect>
        </property>
        <property name="styleSheet">
         <string notr="true">QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7);
border-top-right-radius: 0px;   /* 👈 arrondi seulement coin haut droit */
    border-top-left-radius: 20px;
    border-bottom-left-radius: 20px;
    border-bottom-right-radius: 0px ;
	 font-size: 20px;
 } 
QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);
font-size: 25px; }
</string>
        </property>
        <property name="text">
         <string>Locaux</string>
        </property>
       </widget>
       <widget class="QLabel" name="label_3">
        <property name="geometry">
         <rect>
          <x>0</x>
          <y>10</y>
          <width>151</width>
          <height>111</height>
         </rect>
        </property>
        <property name="text">
         <string/>
        </property>
        <property name="pixmap">
         <pixmap>:/new/prefix1/tt.png</pixmap>
        </property>
       </widget>
       <widget class="QLabel" name="label_4">
        <property name="geometry">
         <rect>
          <x>0</x>
          <y>10</y>
          <width>151</width>
          <height>101</height>
         </rect>
        </property>
        <property name="text">
         <string/>
        </property>
        <property name="pixmap">
         <pixmap>../ESPRIT 2ND YEAR/Projet/week 3_4 improved QT/sss/tt.png</pixmap>
        </property>
       </widget>
       <widget class="QLabel" name="label_16">
        <property name="geometry">
         <rect>
          <x>0</x>
          <y>260</y>
          <width>31</width>
          <height>31</height>
         </rect>
        </property>
        <property name="text">
         <string/>
        </property>
        <property name="pixmap">
         <pixmap>../ESPRIT 2ND YEAR/Projet/week 3_4 improved QT/sss/client-removebg-preview.png</pixmap>
        </property>
       </widget>
       <widget class="QLabel" name="label_17">
        <property name="geometry">
         <rect>
          <x>0</x>
          <y>190</y>
          <width>31</width>
          <height>31</height>
         </rect>
        </property>
        <property name="text">
         <string/>
        </property>
        <property name="pixmap">
         <pixmap>../ESPRIT 2ND YEAR/Projet/week 3_4 improved QT/sss/fournisseurs-removebg-preview-removebg-preview.png</pixmap>
        </property>
       </widget>
       <widget class="QLabel" name="label_18">
        <property name="geometry">
         <rect>
          <x>0</x>
          <y>470</y>
          <width>31</width>
          <height>31</height>
         </rect>
        </property>
        <property name="text">
         <string/>
        </property>
        <property name="pixmap">
         <pixmap>../ESPRIT 2ND YEAR/Projet/week 3_4 improved QT/sss/locaux-removebg-preview.png</pixmap>
        </property>
       </widget>
       <widget class="QLabel" name="label_19">
        <property name="geometry">
         <rect>
          <x>0</x>
          <y>340</y>
          <width>31</width>
          <height>31</height>
         </rect>
        </property>
        <property name="text">
         <string/>
        </property>
        <property name="pixmap">
         <pixmap>../ESPRIT 2ND YEAR/Projet/week 3_4 improved QT/sss/produit-removebg-preview.png</pixmap>
        </property>
       </widget>
       <widget class="QLabel" name="label_20">
        <property name="geometry">
         <rect>
          <x>0</x>
          <y>400</y>
          <width>31</width>
          <height>31</height>
         </rect>
        </property>
        <property name="text">
         <string/>
        </property>
        <property name="pixmap">
         <pixmap>../ESPRIT 2ND YEAR/Projet/week 3_4 improved QT/sss/personal-removebg-preview-removebg-preview.png</pixmap>
        </property>
       </widget>
      </widget>
      <widget class="QWidget" name="layoutWidget">
       <property name="geometry">
        <rect>
         <x>190</x>
         <y>34</y>
         <width>761</width>
         <height>541</height>
        </rect>
       </property>
       <layout class="QVBoxLayout" name="verticalLayout">
        <item>
         <layout class="QHBoxLayout" name="headerLayout">
          <item>
           <widget class="QPushButton" name="btnAjouterClient_4">
            <property name="styleSheet">
             <string notr="true">background-color:#41375f;color:white;font-weight:bold;border-radius:10px;padding:10px 24px;font-size:15px;</string>
            </property>
            <property name="text">
             <string>Ajouter Fournisseur</string>
            </property>
           </widget>
          </item>
          <item>
           <widget class="QPushButton" name="btnExporter_2">
            <property name="styleSheet">
             <string>background-color:#2980b9;color:white;font-weight:bold;border-radius:15px;padding:8px 24px;font-size:15px;</string>
            </property>
            <property name="text">
             <string>Exporter</string>
            </property>
           </widget>
          </item>
         </layout>
        </item>
        <item>
         <widget class="QLabel" name="lblListeClients">
          <property name="font">
           <font>
            <pointsize>16</pointsize>
            <bold>true</bold>
           </font>
          </property>
          <property name="styleSheet">
           <string notr="true">color:#2d224c;font-weight:bold;margin:16px 0 8px 0;
background-color: rgb(255, 255, 255);</string>
          </property>
          <property name="text">
           <string>Liste Des Fournisseurs</string>
          </property>
         </widget>
        </item>
        <item>
         <layout class="QHBoxLayout" name="searchLayout">
          <item>
           <widget class="QLineEdit" name="searchLineEdit">
            <property name="styleSheet">
             <string>background-color:#f5f6fa;border-radius:10px;padding:8px 16px;font-size:14px;</string>
            </property>
            <property name="text">
             <string>Recherche Un Fournisseur</string>
            </property>
            <property name="placeholderText">
             <string>Rechercher par ID ou Nom</string>
            </property>
           </widget>
          </item>
          <item>
           <widget class="QPushButton" name="btnRechercher">
            <property name="styleSheet">
             <string>background-color:#a55eea;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:14px;</string>
            </property>
            <property name="text">
             <string>Trier Par:</string>
            </property>
           </widget>
          </item>
          <item>
           <widget class="QComboBox" name="comboProfession">
            <property name="styleSheet">
             <string>background-color:#f5f6fa;border-radius:10px;padding:8px 16px;font-size:14px;</string>
            </property>
            <property name="editable">
             <bool>false</bool>
            </property>
            <item>
             <property name="text">
              <string>Nom</string>
             </property>
            </item>
           </widget>
          </item>
          <item>
           <widget class="QPushButton" name="btnFilter">
            <property name="styleSheet">
             <string>background-color:#a55eea;color:white;font-weight:bold;border-radius:10px;padding:8px 16px;font-size:14px;</string>
            </property>
            <property name="text">
             <string>Filter</string>
            </property>
           </widget>
          </item>
         </layout>
        </item>
        <item>
         <widget class="QPushButton" name="btnSupprimer_3">
          <property name="styleSheet">
           <string notr="true">background-color:red;color:white;font-weight:bold;border-radius:15px;padding:8px 24px;font-size:15px;</string>
          </property>
          <property name="text">
           <string>Supprimer</string>
          </property>
         </widget>
        </item>
        <item>
         <widget class="QPushButton" name="btnModifier_3">
          <property name="styleSheet">
           <string>background-color:#636e72;color:white;font-weight:bold;border-radius:15px;padding:8px 24px;font-size:15px;</string>
          </property>
          <property name="text">
           <string>Modifier</string>
          </property>
         </widget>
        </item>
        <item>
         <widget class="QTableWidget" name="tableClients">
          <property name="styleSheet">
           <string notr="true">QHeaderView::section { background-color:#2d224c;font-weight:bold; } QTableWidget { background-color:white; }
color: rgb(0, 0, 0);</string>
          </property>
          <row>
           <property name="text">
            <string/>
           </property>
          </row>
          <row>
           <property name="text">
            <string/>
           </property>
          </row>
          <row>
           <property name="text">
            <string/>
           </property>
          </row>
          <column>
           <property name="text">
            <string>ID</string>
           </property>
          </column>
          <column>
           <property name="text">
            <string>Nom</string>
           </property>
          </column>
          <column>
           <property name="text">
            <string>Addresse</string>
           </property>
          </column>
          <column>
           <property name="text">
            <string>Email</string>
           </property>
          </column>
          <column>
           <property name="text">
            <string>Num De Telephone</string>
           </property>
          </column>
          <column>
           <property name="text">
            <string>Status</string>
           </property>
          </column>
          <column>
           <property name="text">
            <string>Produits fourmis</string>
           </property>
          </column>
         </widget>
        </item>
        <item>
         <layout class="QHBoxLayout" name="actionButtonsLayout"/>
        </item>
       </layout>
      </widget>
     </widget>
     <widget class="QToolButton" name="toolButton_3">
      <property name="geometry">
       <rect>
        <x>1040</x>
        <y>160</y>
        <width>191</width>
        <height>51</height>
       </rect>
      </property>
      <property name="styleSheet">
       <string notr="true">QToolButton { border: none; border-radius: 20px; color: white; padding: 10px; background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #9B59B6, stop:1 #BDC3C7);
border-top-right-radius: 0px;   /* 👈 arrondi seulement coin haut droit */
    border-top-left-radius: 20px;
    border-bottom-left-radius: 20px;
    border-bottom-right-radius: 0px ;
	 font-size: 20px;
 } 
QToolButton:hover { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #BDC3C7, stop:1 #F8C8DC);
font-size: 25px; }
</string>
      </property>
      <property name="text">
       <string>Fournisseur</string>
      </property>
     </widget>
     <widget class="QLabel" name="label_2">
      <property name="geometry">
       <rect>
        <x>1000</x>
        <y>80</y>
        <width>151</width>
        <height>111</height>
       </rect>
      </property>
      <property name="text">
       <string/>
      </property>
      <property name="pixmap">
       <pixmap>:/new/prefix1/tt.png</pixmap>
      </property>
     </widget>
     <widget class="QLabel" name="label_11">
      <property name="geometry">
       <rect>
        <x>990</x>
        <y>100</y>
        <width>31</width>
        <height>31</height>
       </rect>
      </property>
      <property name="text">
       <string/>
      </property>
      <property name="pixmap">
       <pixmap>../ESPRIT 2ND YEAR/Projet/week 3_4 improved QT/sss/client-removebg-preview.png</pixmap>
      </property>
     </widget>
     <widget class="QLabel" name="label_12">
      <property name="geometry">
       <rect>
        <x>980</x>
        <y>230</y>
        <width>31</width>
        <height>31</height>
       </rect>
      </property>
      <property name="text">
       <string/>
      </property>
      <property name="pixmap">
       <pixmap>../ESPRIT 2ND YEAR/Projet/week 3_4 improved QT/sss/fournisseurs-removebg-preview-removebg-preview.png</pixmap>
      </property>
     </widget>
     <widget class="QLabel" name="label_13">
      <property name="geometry">
       <rect>
        <x>1010</x>
        <y>275</y>
        <width>31</width>
        <height>31</height>
       </rect>
      </property>
      <property name="text">
       <string/>
      </property>
      <property name="pixmap">
       <pixmap>../ESPRIT 2ND YEAR/Projet/week 3_4 improved QT/sss/locaux-removebg-preview.png</pixmap>
      </property>
     </widget>
     <widget class="QLabel" name="label_14">
      <property name="geometry">
       <rect>
        <x>1020</x>
        <y>315</y>
        <width>31</width>
        <height>31</height>
       </rect>
      </property>
      <property name="text">
       <string/>
      </property>
      <property name="pixmap">
       <pixmap>../ESPRIT 2ND YEAR/Projet/week 3_4 improved QT/sss/produit-removebg-preview.png</pixmap>
      </property>
     </widget>
     <widget class="QLabel" name="label_15">
      <property name="geometry">
       <rect>
        <x>1020</x>
        <y>380</y>
        <width>31</width>
        <height>21</height>
       </rect>
      </property>
      <property name="text">
       <string/>
      </property>
      <property name="pixmap">
       <pixmap>../ESPRIT 2ND YEAR/Projet/week 3_4 improved QT/sss/personal-removebg-preview-removebg-preview.png</pixmap>
      </property>
     </widget>
    </widget>
    <widget class="QWidget" name="page_2">
     <widget class="QTableWidget" name="tableWidget">
      <property name="geometry">
       <rect>
        <x>100</x>
        <y>310</y>
        <width>621</width>
        <height>192</height>
       </rect>
      </property>
      <row>
       <property name="text">
        <string>New Row</string>
       </property>
      </row>
      <row>
       <property name="text">
        <string>New Row</string>
       </property>
      </row>
      <column>
       <property name="text">
        <string>New Column</string>
       </property>
      </column>
      <column>
       <property name="text">
        <string>New Column</string>
       </property>
      </column>
      <column>
       <property name="text">
        <string>New Column</string>
       </property>
      </column>
      <column>
       <property name="text">
        <string>New Column</string>
       </property>
      </column>
      <column>
       <property name="text">
        <string>New Column</string>
       </property>
      </column>
     </widget>
    </widget>
    <widget class="QWidget" name="page_2">
     <widget class="QFrame" name="frameFicheClient">
      <property name="geometry">
       <rect>
        <x>250</x>
        <y>100</y>
        <width>841</width>
        <height>511</height>
       </rect>
      </property>
      <property name="styleSheet">
       <string notr="true">border:2px solid #a55eea; border-radius:20px; background-color:#f5f6fa;
border-color: rgb(0, 0, 127);</string>
      </property>
      <widget class="QLabel" name="lblFicheClient">
       <property name="geometry">
        <rect>
         <x>190</x>
         <y>20</y>
         <width>481</width>
         <height>68</height>
        </rect>
       </property>
       <property name="font">
        <font>
         <pointsize>18</pointsize>
         <bold>true</bold>
        </font>
       </property>
       <property name="styleSheet">
        <string notr="true">color:#6c3fc2;font-weight:bold;margin:16px 0 8px 0;</string>
       </property>
       <property name="text">
        <string>Fiche Client</string>
       </property>
       <property name="alignment">
        <set>Qt::AlignmentFlag::AlignCenter</set>
       </property>
      </widget>
      <widget class="QFrame" name="frame_4">
       <property name="geometry">
        <rect>
         <x>630</x>
         <y>120</y>
         <width>181</width>
         <height>151</height>
        </rect>
       </property>
       <property name="styleSheet">
        <string notr="true"/>
       </property>
       <property name="frameShape">
        <enum>QFrame::Shape::StyledPanel</enum>
       </property>
       <property name="frameShadow">
        <enum>QFrame::Shadow::Raised</enum>
       </property>
      </widget>
      <widget class="QLabel" name="label">
       <property name="geometry">
        <rect>
         <x>60</x>
         <y>130</y>
         <width>91</width>
         <height>20</height>
        </rect>
       </property>
       <property name="styleSheet">
        <string notr="true">background-color: rgb(48, 71, 120);</string>
       </property>
       <property name="text">
        <string>ID</string>
       </property>
      </widget>
      <widget class="QLabel" name="label_5">
       <property name="geometry">
        <rect>
         <x>60</x>
         <y>170</y>
         <width>91</width>
         <height>20</height>
        </rect>
       </property>
       <property name="styleSheet">
        <string notr="true">background-color: rgb(48, 71, 120);</string>
       </property>
       <property name="text">
        <string>Nom</string>
       </property>
      </widget>
      <widget class="QLabel" name="label_6">
       <property name="geometry">
        <rect>
         <x>60</x>
         <y>210</y>
         <width>91</width>
         <height>20</height>
        </rect>
       </property>
       <property name="styleSheet">
        <string notr="true">background-color: rgb(48, 71, 120);</string>
       </property>
       <property name="text">
        <string>Prénom</string>
       </property>
      </widget>
      <widget class="QLabel" name="label_7">
       <property name="geometry">
        <rect>
         <x>62</x>
         <y>290</y>
         <width>91</width>
         <height>20</height>
        </rect>
       </property>
       <property name="styleSheet">
        <string notr="true">background-color: rgb(48, 71, 120);</string>
       </property>
       <property name="text">
        <string>Telephone</string>
       </property>
      </widget>
      <widget class="QLabel" name="label_8">
       <property name="geometry">
        <rect>
         <x>60</x>
         <y>250</y>
         <width>91</width>
         <height>20</height>
        </rect>
       </property>
       <property name="styleSheet">
        <string notr="true">background-color: rgb(48, 71, 120);</string>
       </property>
       <property name="text">
        <string>Date d'inscri</string>
       </property>
      </widget>
      <widget class="QLabel" name="label_9">
       <property name="geometry">
        <rect>
         <x>60</x>
         <y>330</y>
         <width>91</width>
         <height>21</height>
        </rect>
       </property>
       <property name="styleSheet">
        <string notr="true">background-color: rgb(48, 71, 120);</string>
       </property>
       <property name="text">
        <string>Date D'anniv</string>
       </property>
      </widget>
      <widget class="QLabel" name="label_10">
       <property name="geometry">
        <rect>
         <x>60</x>
         <y>380</y>
         <width>121</width>
         <height>41</height>
        </rect>
       </property>
       <property name="styleSheet">
        <string notr="true">background-color: rgb(48, 71, 120);</string>
       </property>
       <property name="text">
        <string>statut de fidelité</string>
       </property>
      </widget>
      <widget class="QWidget" name="layoutWidget">
       <property name="geometry">
        <rect>
         <x>580</x>
         <y>450</y>
         <width>240</width>
         <height>42</height>
        </rect>
       </property>
       <layout class="QHBoxLayout" name="ajouterActionLayout">
        <item>
         <widget class="QPushButton" name="btnConfirmer">
          <property name="styleSheet">
           <string>background-color:#2980b9;color:white;font-weight:bold;border-radius:15px;padding:8px 24px;font-size:15px;</string>
          </property>
          <property name="text">
           <string>Confirmer</string>
          </property>
         </widget>
        </item>
        <item>
         <widget class="QPushButton" name="btnAnnuler">
          <property name="styleSheet">
           <string>background-color:#636e72;color:white;font-weight:bold;border-radius:15px;padding:8px 24px;font-size:15px;</string>
          </property>
          <property name="text">
           <string>Annuler</string>
          </property>
         </widget>
        </item>
       </layout>
      </widget>
      <widget class="QLineEdit" name="lineEditNom">
       <property name="geometry">
        <rect>
         <x>240</x>
         <y>170</y>
         <width>251</width>
         <height>26</height>
        </rect>
       </property>
       <property name="placeholderText">
        <string>Nom</string>
       </property>
      </widget>
      <widget class="QLineEdit" name="lineEditPhone">
       <property name="geometry">
        <rect>
         <x>240</x>
         <y>290</y>
         <width>251</width>
         <height>26</height>
        </rect>
       </property>
       <property name="placeholderText">
        <string>Phone Number</string>
       </property>
      </widget>
      <widget class="QCheckBox" name="checkNew">
       <property name="geometry">
        <rect>
         <x>340</x>
         <y>390</y>
         <width>58</width>
         <height>24</height>
        </rect>
       </property>
       <property name="styleSheet">
        <string notr="true">background-color: rgb(70, 88, 127);</string>
       </property>
       <property name="text">
        <string>New</string>
       </property>
      </widget>
      <widget class="QLineEdit" name="lineEditDateNaissance">
       <property name="geometry">
        <rect>
         <x>240</x>
         <y>330</y>
         <width>251</width>
         <height>26</height>
        </rect>
       </property>
       <property name="placeholderText">
        <string>Date de naissance</string>
       </property>
      </widget>
      <widget class="QLineEdit" name="lineEditID">
       <property name="geometry">
        <rect>
         <x>240</x>
         <y>130</y>
         <width>251</width>
         <height>26</height>
        </rect>
       </property>
       <property name="placeholderText">
        <string>ID</string>
       </property>
      </widget>
      <widget class="QLineEdit" name="lineEditPrenom">
       <property name="geometry">
        <rect>
         <x>240</x>
         <y>210</y>
         <width>251</width>
         <height>26</height>
        </rect>
       </property>
       <property name="placeholderText">
        <string>Prénom</string>
       </property>
      </widget>
      <widget class="QCheckBox" name="checkOld">
       <property name="geometry">
        <rect>
         <x>250</x>
         <y>390</y>
         <width>52</width>
         <height>24</height>
        </rect>
       </property>
       <property name="styleSheet">
        <string notr="true">background-color: rgb(70, 88, 127);</string>
       </property>
       <property name="text">
        <string>Old</string>
       </property>
      </widget>
      <widget class="QCheckBox" name="checkVIP">
       <property name="geometry">
        <rect>
         <x>440</x>
         <y>390</y>
         <width>49</width>
         <height>24</height>
        </rect>
       </property>
       <property name="styleSheet">
        <string notr="true">background-color: rgb(70, 88, 127);</string>
       </property>
       <property name="text">
        <string>VIP</string>
       </property>
      </widget>
      <widget class="QLineEdit" name="lineEditDateInscription">
       <property name="geometry">
        <rect>
         <x>240</x>
         <y>250</y>
         <width>251</width>
         <height>26</height>
        </rect>
       </property>
       <property name="placeholderText">
        <string>Date d'Inscription</string>
       </property>
      </widget>
     </widget>
     <widget class="QPushButton" name="btnListeClients_2">
      <property name="geometry">
       <rect>
        <x>250</x>
        <y>40</y>
        <width>360</width>
        <height>40</height>
       </rect>
      </property>
      <property name="styleSheet">
       <string notr="true">background-color:#41375f;color:white;font-weight:bold;border-radius:10px;padding:10px 24px;font-size:15px;</string>
      </property>
      <property name="text">
       <string>Liste des clients</string>
      </property>
     </widget>
     <widget class="QPushButton" name="btnAjouterClient_2">
      <property name="geometry">
       <rect>
        <x>670</x>
        <y>40</y>
        <width>360</width>
        <height>40</height>
       </rect>
      </property>
      <property name="styleSheet">
       <string notr="true">background-color:#41375f;color:white;font-weight:bold;border-radius:10px;padding:10px 24px;font-size:15px;</string>
      </property>
      <property name="text">
       <string>Ajouter client</string>
      </property>
     </widget>
     <widget class="QPushButton" name="btnClient_2">
      <property name="geometry">
       <rect>
        <x>50</x>
        <y>170</y>
        <width>93</width>
        <height>45</height>
       </rect>
      </property>
      <property name="styleSheet">
       <string>background-color:#a55eea;color:white;font-weight:bold;text-align:left;padding:12px 24px;font-size:16px;border-radius:8px;</string>
      </property>
      <property name="text">
       <string>Client</string>
      </property>
     </widget>
    </widget>
   </widget>
  </widget>
  <widget class="QMenuBar" name="menubar">
   <property name="geometry">
    <rect>
     <x>0</x>
     <y>0</y>
     <width>1171</width>
     <height>22</height>
    </rect>
   </property>
  </widget>
  <widget class="QStatusBar" name="statusbar"/>
 </widget>
 <resources/>
 <connections/>
</ui>
