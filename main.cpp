//
// Created by Lenovo on 2022/1/11.
//
#include "Account.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int num=0;
//用到的函数
void showMain(Account accounts[]);
void login(Account accounts[]);
static int getIndexBycardId(string &cardId,Account accounts[]);
void Register(Account accounts[]);
static string creatCardId(Account accounts[]);
static void showUserCommand(Account &acc,Account accounts[]);
static void showAccount(Account &acc);
static void depositMoney(Account &acc);
static void drawMoney(Account &acc);
static void transferMoney(Account accounts[],Account &acc);
static void updatePassword(Account &acc);
void remove(Account accounts[],Account &acc);
int main(){
    Account accounts[100];
    showMain(accounts);//首页
    return 0;
}
void showMain(Account accounts[]){
    cout<<"==================欢迎进入首页====================="<<endl;
    while (true){
        cout<<"请输入你想做的操作"<<endl;
        cout<<"1.登录"<<endl;
        cout<<"2.开户"<<endl;
        cout<<"0.退出"<<endl;
        cout<<"您可以输入了："<<endl;
//        cout<<num<<endl;
//        cout<<accounts[0].getMoney()<<endl;
        //cout<<accounts[1].getMoney();
        char command;
        cin>>command;
        switch (command) {
            case '1'://登录
                login(accounts);
                break;
            case '2'://注册
                Register(accounts);
                break;
            case '0':
                return;
            default:
                cout<<"您当前输入的操作命令不被支持！";
        }
    }
}
static void updatePassword(Account &acc){
    cout<<"=================修改密码=================="<<endl;
    while (true){
        cout<<"请输入原密码："<<endl;
        string okPassword;
        cin>>okPassword;
        if(!acc.getPassWord().compare(okPassword)){
            while (true){
                //可以输入密码
                cout<<"请您输入新密码："<<endl;
                string newPassword;
                cin>>newPassword;
                cout<<"请您确认新密码："<<endl;
                string oknewPassword;
                cin>>oknewPassword;
                if(!newPassword.compare(oknewPassword)){
                    acc.setPassWord(newPassword);
                    return;
                } else{
                    cout<<"两次输入密码不一致！"<<endl;
                }
            }
        } else{
            cout<<"当前输入密码不正确！"<<endl;
        }
    }
}

void Register(Account accounts[]){//开户功能
    cout<<"===============用户开户功能=================="<<endl;
    cout<<"请您输入开户名称："<<endl;
    string name;
    cin>>name;
    string password = "";
    while (true){
        cout<<"请您输入开户密码："<<endl;
        cin>>password;
        cout<<"请您输入确认密码："<<endl;
        string okPassword;
        cin>>okPassword;
        if(!okPassword.compare(password)){
            break;
        } else{
            cout<<"两次密码必须一致！请重新输入"<<endl;
        }
    }
    cout<<"请您输入单次限额："<<endl;
    double quotaMoney;
    cin>>quotaMoney;
    string cardId = creatCardId(accounts);
    Account *account = new Account(cardId, name, password, quotaMoney,0);
    accounts[num++]=(*account);
    cout<<"开户成功！您的卡号是："<<account->getCardId()<<endl;
}
static string creatCardId(Account accounts[]){
    while (true){
        //生成八位随机数
        string cardId = "";
        for (int i = 0; i < 8; ++i) {
            int r = rand()%10;
            cardId += to_string(r);
        }
        //判断是否重复
        int flag = getIndexBycardId(cardId,accounts);
        if(flag==-1){
            return cardId;
        }
    }
}

void login(Account accounts[]){
    //账户不存在
    if(num==0){
        cout<<"当前系统无任何账户，您需要先注册！"<<endl;
        return;
    }
    //让用户键盘输入卡号
    while(true){
        cout<<"请您输入登录卡号："<<endl;
        string cardId;
        cin>>cardId;
        int flag = getIndexBycardId(cardId,accounts);
        //Account acc = getAccountBycardId(cardId,accounts);
        Account* acc;
        if(flag!=-1){//用户对象存在
            while (true){
                for (int i = 0; i < num; ++i) {
                    if(!accounts[i].getCardId().compare(cardId)){
                        acc = &accounts[i];
                    }
                }
                cout<<"请输入登录密码"<<endl;
                string password;
                cin>>password;
                if(!acc->getPassWord().compare(password)){
                    //登录成功
                    cout<<"恭喜您，"<<acc->getUserName()<<"先生/女士成功进入系统，您的卡号是："
                        <<acc->getCardId()<<endl;
                    showUserCommand(*acc,accounts);
                    return;
                } else{
                    cout<<"您的密码有误，请重新输入！"<<endl;
                }
            }
        } else{
            cout<<"对不起，不存在该卡号的用户！"<<endl;
        }
    }
}
static void showUserCommand(Account &acc,Account accounts[]){
    while (true){
        cout<<"===============用户操作界面==============="<<endl;
        cout<<"1.查询账户"<<endl;
        cout<<"2.存款"<<endl;
        cout<<"3.取款"<<endl;
        cout<<"4.转账"<<endl;
        cout<<"5.修改密码"<<endl;
        cout<<"6.退出"<<endl;
        cout<<"7.注销账户"<<endl;
        cout<<"请您输入命令："<<endl;
        //cout<<accounts[0].getMoney()<<endl;
        int command;
        cin>>command;
        switch (command) {
            case 1:
                showAccount(acc);
                break;
            case 2:
                depositMoney(acc);
                break;
            case 3:
                drawMoney(acc);
                break;
            case 4:
                transferMoney(accounts,acc);
                break;
            case 5:
                updatePassword(acc);
                break;
            case 6:
                cout<<"欢迎下次光临！"<<endl;
                return;
            case 7:
                remove(accounts,acc);
                return;
            default:
                cout<<"输入有误！"<<endl;
        }

    }
}
void remove(Account accounts[],Account &acc){
    for (int i = 0; i < num ;++i) {
        if(!accounts[i].getCardId().compare(acc.getCardId())){
            //找到销户的用户
            for (int j = 0; j < num; ++j) {
                accounts[j] = accounts[j+1];
            }
            cout<<"销户成功！"<<endl;
        }
    }
    num--;
}
int startsWith(string s, string sub){
    return s.find(sub)==0?1:0;
}
static void transferMoney(Account accounts[],Account &acc){
    //系统有两个用户及以上才可以转账
    if(num<2){
        cout<<"对不起，系统中无其他账户，您不可以直接转账！"<<endl;
        return;
    }
    if(acc.getMoney()==0){
        cout<<"对不起，您的余额不足，无法转账！"<<endl;
        return;
    }
    while (true){
        cout<<"请输入对方账户的卡号："<<endl;
        string cardId;
        cin>>cardId;
//        Account account = getAccountBycardId(cardId,accounts);
//        if(account.getMoney()!=-1){
//            //判断转账对象是否为登录人
//            if(!acc.getCardId().compare(cardId)){
//                cout<<"不可以给自己转账！"<<endl;
        int flag = getIndexBycardId(cardId,accounts);
        //Account acc = getAccountBycardId(cardId,accounts);
        Account* account;
        if(flag!=-1){//用户对象存在
            if (!acc.getCardId().compare(cardId)) {
                cout<<"不可以给自己转账！"<<endl;
                    }
            else{
                for (int i = 0; i < num; ++i) {
                    if(!accounts[i].getCardId().compare(cardId)){
                        account = &accounts[i];
                    }
                }
                //先确认对方姓氏
                string name = "*" + account->getUserName().substr(1);
                cout<<"请您确认["<<name<<"]的姓氏："<<endl;
                string preName;
                cin>>preName;
                if(startsWith(account->getUserName(),preName)){
                    //开始转账
                    cout<<"请输入转账金额"<<endl;
                    double money;
                    cin>>money;
                    if(money>acc.getMoney()){
                        cout<<"对不起，您的余额不足，最多能转账："<<acc.getMoney()<<"元"<<endl;
                    } else{
                        //可以转账
                        acc.setMoney(acc.getMoney()-money);
                        account->setMoney(account->getMoney()+money);
                        cout<<"转账成功！已经为"<<account->getUserName()<<"转账"
                            <<money<<"元"<<endl;
                       // cout<<account->getMoney();//debug
                        showAccount(acc);
                        return;
                    }
                } else{
                    cout<<"对不起，您认证有误！"<<endl;
                }
            }
        } else{
            cout<<"对不起，您输入的转账卡号有误！"<<endl;
        }
    }
}
static void drawMoney(Account &acc){
    cout<<"==================取款操作================"<<endl;
    while (true){
        //判断用户存款是否超过100
        if(acc.getMoney()>=100){
            cout<<"请您输入取款金额"<<endl;
            double money;
            cin>>money;
            if(money>acc.getQuotaMoney()){
                cout<<"您本次取款超过取款限额，每次最多可以取"<<acc.getQuotaMoney()<<"元"<<endl;
            } else{
                //再判断余额
                if(acc.getMoney()>=money){
                    //可以取钱
                    acc.setMoney(acc.getMoney()-money);
                    cout<<"取钱"<<money<<"成功,还剩:"<<acc.getMoney()<<"元"<<endl;
                    return;
                } else{
                    cout<<"余额不足！"<<endl;
                }
            }
        } else{
            cout<<"您的账户余额不足100，不能取款！"<<endl;
            break;
        }
    }
}
static void depositMoney(Account &acc){
    cout<<"==================存钱操作================="<<endl;
    cout<<"请您输入存款金额："<<endl;
    double money;
    cin>>money;
    acc.setMoney(acc.getMoney()+money);
    cout<<"存款完成!"<<endl;
    showAccount(acc);
}
static void showAccount(Account &acc){
    cout<<"===================当前账户详情===================="<<endl;
    cout<<"卡号："<<acc.getCardId()<<endl;
    cout<<"姓名："<<acc.getUserName()<<endl;
    cout<<"余额："<<acc.getMoney()<<endl;
    cout<<"单次限额："<<acc.getQuotaMoney()<<endl;
}
static int getIndexBycardId(string &cardId,Account accounts[]){
    for (int i = 0; i < num; ++i) {
        Account acc = accounts[i];
        if(!(acc.getCardId().compare(cardId))){
            return i;
        }
    }
    return -1;
}
