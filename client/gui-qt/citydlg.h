/**************************************************************************
 Copyright (c) 1996-2020 Freeciv21 and Freeciv contributors. This file is
 part of Freeciv21. Freeciv21 is free software: you can redistribute it
 and/or modify it under the terms of the GNU  General Public License  as
 published by the Free Software Foundation, either version 3 of the
 License,  or (at your option) any later version. You should have received
 a copy of the GNU General Public License along with Freeciv21. If not,
 see https://www.gnu.org/licenses/.
**************************************************************************/
#pragma once

#include "fc_types.h"
// Qt
#include "fc_types.h"
#include <QDialog>
#include <QElapsedTimer>
#include <QGroupBox>
#include <QItemDelegate>
#include <QLabel>
#include <QProgressBar>
#include <QTableWidget>
#include <QToolTip>
#include <QtMath>
// gui-qt
#include "dialogs.h"

class QAction;
class QCheckBox;
class QCloseEvent;
class QContextMenuEvent;
class QEvent;
class QFont;
class QGridLayout;
class QGroupBox;
class QHBoxLayout;
class QHideEvent;
class QItemSelection;
class QMenu;
class QMouseEvent;
class QPaintEvent;
class QPainter;
class QPushButton;
class QRadioButton;
class QRect;
class QResizeEvent;
class QShowEvent;
class QSlider;
class QSplitter;
class QTableWidget;
class QTableWidgetItem;
class QTimerEvent;
class QVBoxLayout;
class QVariant;
class fc_tooltip;
struct canvas;

#define NUM_INFO_FIELDS 15
/****************************************************************************
  Custom progressbar with animated progress and right click event
****************************************************************************/
class progress_bar : public QProgressBar {
  Q_OBJECT
  QElapsedTimer m_timer;
signals:
  void clicked();

public:
  progress_bar(QWidget *parent);
  ~progress_bar();
  void mousePressEvent(QMouseEvent *event) { emit clicked(); }
  void set_pixmap(struct universal *target);
  void set_pixmap(int n);

protected:
  void paintEvent(QPaintEvent *event);
  void timerEvent(QTimerEvent *event);
  void resizeEvent(QResizeEvent *event);

private:
  void create_region();
  int m_animate_step;
  QPixmap *pix;
  QRegion reg;
  QFont *sfont;
};

/****************************************************************************
  Single item on unit_info in city dialog representing one unit
****************************************************************************/
class unit_item : public QLabel {
  Q_OBJECT
  QAction *disband_action;
  QAction *change_home;
  QAction *activate;
  QAction *activate_and_close;
  QAction *sentry;
  QAction *fortify;
  QAction *load;
  QAction *unload;
  QAction *upgrade;
  QAction *unload_trans;
  QMenu *unit_menu;

public:
  unit_item(QWidget *parent, struct unit *punit, bool supp = false,
            int happy_cost = 0);
  ~unit_item();
  void init_pix();

private:
  struct unit *qunit;
  QImage unit_img;
  void contextMenuEvent(QContextMenuEvent *ev);
  void create_actions();
  int happy_cost;
  bool supported;

private slots:
  void disband();
  void change_homecity();
  void activate_unit();
  void activate_and_close_dialog();
  void sentry_unit();
  void fortify_unit();
  void upgrade_unit();
  void load_unit();
  void unload_unit();
  void unload_all();

protected:
  void mousePressEvent(QMouseEvent *event);
  void leaveEvent(QEvent *event);
  void enterEvent(QEvent *event);
};

/****************************************************************************
  Shows list of units ( as labels - unit_info )
****************************************************************************/
class unit_info : public QFrame {

  Q_OBJECT

public:
  unit_info();
  ~unit_info();
  void add_item(unit_item *item);
  void init_layout();
  void update_units();
  void clear_layout();
  void set_supp(bool);
  QHBoxLayout *layout;
  QList<unit_item *> unit_list;

private:
  bool supports;

};

/****************************************************************************
  Single item on unit_info in city dialog representing one unit
****************************************************************************/
class impr_item : public QLabel {
  Q_OBJECT

public:
  impr_item(QWidget *parent, const struct impr_type *building,
            struct city *pcity);
  ~impr_item();
  void init_pix();

private:
  const struct impr_type *impr;
  struct canvas *impr_pixmap;
  struct city *pcity;

protected:
  void mouseDoubleClickEvent(QMouseEvent *event);
  void leaveEvent(QEvent *event);
  void enterEvent(QEvent *event);
};

/****************************************************************************
  Shows list of improvemrnts
****************************************************************************/
class impr_info : public QFrame {
  Q_OBJECT
public:
  impr_info();
  ~impr_info();
  void add_item(impr_item *item);
  void init_layout();
  void update_buildings();
  void clear_layout();
  QHBoxLayout *layout;
  QList<impr_item *> impr_list;
};

/****************************************************************************
  Item delegate for production popup
****************************************************************************/
class city_production_delegate : public QItemDelegate {
  Q_OBJECT

public:
  city_production_delegate(QPoint sh, QObject *parent, struct city *city);
  ~city_production_delegate() {}
  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const;
  QSize sizeHint(const QStyleOptionViewItem &option,
                 const QModelIndex &index) const;

private:
  int item_height;
  QPoint pd;
  struct city *pcity;

protected:
  void drawFocus(QPainter *painter, const QStyleOptionViewItem &option,
                 const QRect &rect) const;
};

/****************************************************************************
  Single item in production popup
****************************************************************************/
class production_item : public QObject {
  Q_OBJECT

public:
  production_item(struct universal *ptarget, QObject *parent);
  ~production_item();
  inline int columnCount() const { return 1; }
  QVariant data() const;
  bool setData();

private:
  struct universal *target;
};

/***************************************************************************
  City production model
***************************************************************************/
class city_production_model : public QAbstractListModel {
  Q_OBJECT

public:
  city_production_model(struct city *pcity, bool f, bool su, bool sw,
                        bool sb, QObject *parent = 0);
  ~city_production_model();
  inline int rowCount(const QModelIndex &index = QModelIndex()) const
  {
    Q_UNUSED(index);
    return (qCeil(static_cast<float>(city_target_list.size()) / 3));
  }
  int columnCount(const QModelIndex &parent = QModelIndex()) const
  {
    Q_UNUSED(parent);
    return 3;
  }
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::DisplayRole);
  QPoint size_hint();
  void populate();
  QPoint sh;

private:
  QList<production_item *> city_target_list;
  struct city *mcity;
  bool future_t;
  bool show_units;
  bool show_buildings;
  bool show_wonders;
};

/****************************************************************************
  Class for popup avaialable production
****************************************************************************/
class production_widget : public QTableView {
  Q_OBJECT

  city_production_model *list_model;
  city_production_delegate *c_p_d;

public:
  production_widget(QWidget *parent, struct city *pcity, bool future,
                    int when, int curr, bool show_units, bool buy = false,
                    bool show_wonders = true, bool show_buildings = true);
  ~production_widget();

public slots:
  void prod_selected(const QItemSelection &sl, const QItemSelection &ds);

protected:
  void mousePressEvent(QMouseEvent *event);
  bool eventFilter(QObject *obj, QEvent *ev);

private:
  struct city *pw_city;
  int when_change;
  int curr_selection;
  bool sh_units;
  bool buy_it;
  fc_tooltip *fc_tt;
};

/****************************************************************************
  city_label is used only for showing citizens icons
  and was created to catch mouse events
****************************************************************************/
class city_label : public QLabel {
  Q_OBJECT

public:
  city_label(QWidget *parent = 0);
  void set_city(struct city *pcity);
  void set_type(int);

private:
  struct city *pcity;
  int type;

protected:
  void mousePressEvent(QMouseEvent *event);
};

class city_info : public QWidget {
  Q_OBJECT
public:
  city_info(QWidget *parent = 0);
  void update_labels(struct city *ci_city);
private:
  QLabel *qlt[NUM_INFO_FIELDS];
  int positions;
};


class governor_sliders : public QGroupBox {
  Q_OBJECT
public:
  governor_sliders(QWidget *parent = 0);
  void update_sliders(struct cm_parameter &param);
  QCheckBox *cma_celeb_checkbox;
  QSlider *slider_tab[2 * O_LAST + 2];
private slots:
  void cma_slider(int val);
  void cma_celebrate_changed(int val);
};


#include "ui_citydlg.h"
/****************************************************************************
  City dialog
****************************************************************************/
class city_dialog : public qfc_dialog {

  Q_OBJECT
  Q_DISABLE_COPY(city_dialog);
  Ui::FormCityDlg ui;
  QPixmap *citizen_pixmap;
  bool future_targets, show_units, show_wonders, show_buildings;
  int selected_row_p;
  city_label *lab_table[6];
public:
  static city_dialog *instance();
  static void drop();
  ~city_dialog();
  void setup_ui(struct city *qcity);
  void refresh();
  void cma_check_agent();
  struct city *pcity;
  int scroll_height;

private:
  city_dialog(QWidget *parent = 0);
  static city_dialog *m_instance;
  int current_building;
  void update_title();
  void update_building();
  void update_info_label();
  void update_buy_button();
  void update_citizens();
  void update_improvements();
  void update_units();
  void update_nation_table();
  void update_cma_tab();
  void update_disabled();
  void update_sliders();
  void update_prod_buttons();
  void change_production(bool next);

private slots:
  void next_city();
  void prev_city();
  void production_changed(int index);
  void show_targets();
  void show_targets_worklist();
  void buy();
  void dbl_click_p(QTableWidgetItem *item);
  void delete_prod();
  void item_selected(const QItemSelection &sl, const QItemSelection &ds);
  void clear_worklist();
  void save_worklist();
  void worklist_up();
  void worklist_down();
  void worklist_del();
  void display_worklist_menu(const QPoint);
  void disband_state_changed(bool allow_disband);
  void cma_remove();
  void cma_enable();
  void cma_changed();
  void cma_selected(const QItemSelection &sl, const QItemSelection &ds);
  void cma_double_clicked(int row, int column);
  void cma_context_menu(const QPoint p);
  void save_cma();
  void city_rename();

protected:
  void showEvent(QShowEvent *event);
  void hideEvent(QHideEvent *event);
  void closeEvent(QCloseEvent *event);
  bool eventFilter(QObject *obj, QEvent *event);
};

void destroy_city_dialog();
void city_font_update();
