/*
 * cashierwidget.h
 * Copyright 2017 - ~, Apin <apin.klas@gmail.com>
 *
 * This file is part of Sultan.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CASHIERWIDGET_H
#define CASHIERWIDGET_H

#include "messagehandler.h"
#include "customer/customer.h"
#include <QWidget>

namespace Ui {
class CashierWidget;
}

namespace LibGUI {

class CashierTableModel;
class PayCashDialog;
class AdvancePaymentDialog;
class PayCashlessDialog;

class CashierWidget : public QWidget, public LibG::MessageHandler
{
    Q_OBJECT

public:
    CashierWidget(LibG::MessageBus *bus, QWidget *parent = 0);
    ~CashierWidget();
    void showEvent(QShowEvent *event) override;

protected:
    void messageReceived(LibG::Message *msg) override;

private:
    Ui::CashierWidget *ui;
    float mCount = 0.0f;
    CashierTableModel *mModel;
    PayCashDialog *mPayCashDialog;
    int mSaveSlot = -1;
    AdvancePaymentDialog *mAdvancePaymentDialog;
    PayCashlessDialog *mPayCashlessDialog;

    void cutPaper();
    void saveToSlot(int slot);
    void loadFromSlot(int slot);
    void removeSlot(int slot);
    void updateCustomerLabel();
    double getTax();

private slots:
    void barcodeEntered();
    void totalChanged(double value);
    void selectRow(const QModelIndex &index);
    void tableKeyPressed(QObject *sender, QKeyEvent *event);
    void payCash();
    void payCashless();
    void payAdvance();
    void openDrawer();
    void updateLastInputed();
    void payRequested(int type, double value);
    void printBill(const QVariantMap &data);
    void openSearch();
    void openPreviousTransaction();
    void newTransaction();
    void saveCartTriggered();
    void loadCartTriggered();
    void openHelp();
    void scanCustomer();
    void resetCustomer(bool dontShowMessage = false);
    void openCheckPrice();
};

}
#endif // CASHIERWIDGET_H
