
//Account.h
//
// Created by Lenovo on 2022/1/11.
//

#ifndef ATMSYSTEM_ACCOUNT_H
#define ATMSYSTEM_ACCOUNT_H

#endif //ATMSYSTEM_ACCOUNT_H
#include <iostream>
#include <string>

using namespace std;
class Account{
private:
    string cardId;//卡号
    string userName;
    string passWord;
    double money;
    double quotaMoney;//当次取现额度
public:
    Account() {}//无参构造函数

    virtual ~Account() {
    }//析构

    Account(const string &cardId,const string &userName, const string &passWord,
            double quotaMoney,double money) : cardId(cardId),userName(userName),passWord(passWord)
            ,quotaMoney(quotaMoney),money(money) {}

    const string &getCardId() const {
        return cardId;
    }

    const string &getUserName() const {
        return userName;
    }

    const string &getPassWord() const {
        return passWord;
    }

    double getMoney() const {
        return money;
    }

    double getQuotaMoney() const {
        return quotaMoney;
    }

    void setCardId(const string &cardId) {
        this->cardId = cardId;
    }

    void setUserName(const string &userName) {
        this->userName = userName;
    }

    void setPassWord(const string &passWord) {
        this->passWord = passWord;
    }

    void setMoney(double money) {
        this->money = money;
    }

    void setQuotaMoney(double quotaMoney) {
        this->quotaMoney = quotaMoney;
    }
};
