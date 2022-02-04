//
// Created by Lenovo on 2022/1/11.
//
#include "Account.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int num=0;
//�õ��ĺ���
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
    showMain(accounts);//��ҳ
    return 0;
}
void showMain(Account accounts[]){
    cout<<"==================��ӭ������ҳ====================="<<endl;
    while (true){
        cout<<"�������������Ĳ���"<<endl;
        cout<<"1.��¼"<<endl;
        cout<<"2.����"<<endl;
        cout<<"0.�˳�"<<endl;
        cout<<"�����������ˣ�"<<endl;
//        cout<<num<<endl;
//        cout<<accounts[0].getMoney()<<endl;
        //cout<<accounts[1].getMoney();
        char command;
        cin>>command;
        switch (command) {
            case '1'://��¼
                login(accounts);
                break;
            case '2'://ע��
                Register(accounts);
                break;
            case '0':
                return;
            default:
                cout<<"����ǰ����Ĳ��������֧�֣�";
        }
    }
}
static void updatePassword(Account &acc){
    cout<<"=================�޸�����=================="<<endl;
    while (true){
        cout<<"������ԭ���룺"<<endl;
        string okPassword;
        cin>>okPassword;
        if(!acc.getPassWord().compare(okPassword)){
            while (true){
                //������������
                cout<<"�������������룺"<<endl;
                string newPassword;
                cin>>newPassword;
                cout<<"����ȷ�������룺"<<endl;
                string oknewPassword;
                cin>>oknewPassword;
                if(!newPassword.compare(oknewPassword)){
                    acc.setPassWord(newPassword);
                    return;
                } else{
                    cout<<"�����������벻һ�£�"<<endl;
                }
            }
        } else{
            cout<<"��ǰ�������벻��ȷ��"<<endl;
        }
    }
}

void Register(Account accounts[]){//��������
    cout<<"===============�û���������=================="<<endl;
    cout<<"�������뿪�����ƣ�"<<endl;
    string name;
    cin>>name;
    string password = "";
    while (true){
        cout<<"�������뿪�����룺"<<endl;
        cin>>password;
        cout<<"��������ȷ�����룺"<<endl;
        string okPassword;
        cin>>okPassword;
        if(!okPassword.compare(password)){
            break;
        } else{
            cout<<"�����������һ�£�����������"<<endl;
        }
    }
    cout<<"�������뵥���޶"<<endl;
    double quotaMoney;
    cin>>quotaMoney;
    string cardId = creatCardId(accounts);
    Account *account = new Account(cardId, name, password, quotaMoney,0);
    accounts[num++]=(*account);
    cout<<"�����ɹ������Ŀ����ǣ�"<<account->getCardId()<<endl;
}
static string creatCardId(Account accounts[]){
    while (true){
        //���ɰ�λ�����
        string cardId = "";
        for (int i = 0; i < 8; ++i) {
            int r = rand()%10;
            cardId += to_string(r);
        }
        //�ж��Ƿ��ظ�
        int flag = getIndexBycardId(cardId,accounts);
        if(flag==-1){
            return cardId;
        }
    }
}

void login(Account accounts[]){
    //�˻�������
    if(num==0){
        cout<<"��ǰϵͳ���κ��˻�������Ҫ��ע�ᣡ"<<endl;
        return;
    }
    //���û��������뿨��
    while(true){
        cout<<"���������¼���ţ�"<<endl;
        string cardId;
        cin>>cardId;
        int flag = getIndexBycardId(cardId,accounts);
        //Account acc = getAccountBycardId(cardId,accounts);
        Account* acc;
        if(flag!=-1){//�û��������
            while (true){
                for (int i = 0; i < num; ++i) {
                    if(!accounts[i].getCardId().compare(cardId)){
                        acc = &accounts[i];
                    }
                }
                cout<<"�������¼����"<<endl;
                string password;
                cin>>password;
                if(!acc->getPassWord().compare(password)){
                    //��¼�ɹ�
                    cout<<"��ϲ����"<<acc->getUserName()<<"����/Ůʿ�ɹ�����ϵͳ�����Ŀ����ǣ�"
                        <<acc->getCardId()<<endl;
                    showUserCommand(*acc,accounts);
                    return;
                } else{
                    cout<<"���������������������룡"<<endl;
                }
            }
        } else{
            cout<<"�Բ��𣬲����ڸÿ��ŵ��û���"<<endl;
        }
    }
}
static void showUserCommand(Account &acc,Account accounts[]){
    while (true){
        cout<<"===============�û���������==============="<<endl;
        cout<<"1.��ѯ�˻�"<<endl;
        cout<<"2.���"<<endl;
        cout<<"3.ȡ��"<<endl;
        cout<<"4.ת��"<<endl;
        cout<<"5.�޸�����"<<endl;
        cout<<"6.�˳�"<<endl;
        cout<<"7.ע���˻�"<<endl;
        cout<<"�����������"<<endl;
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
                cout<<"��ӭ�´ι��٣�"<<endl;
                return;
            case 7:
                remove(accounts,acc);
                return;
            default:
                cout<<"��������"<<endl;
        }

    }
}
void remove(Account accounts[],Account &acc){
    for (int i = 0; i < num ;++i) {
        if(!accounts[i].getCardId().compare(acc.getCardId())){
            //�ҵ��������û�
            for (int j = 0; j < num; ++j) {
                accounts[j] = accounts[j+1];
            }
            cout<<"�����ɹ���"<<endl;
        }
    }
    num--;
}
int startsWith(string s, string sub){
    return s.find(sub)==0?1:0;
}
static void transferMoney(Account accounts[],Account &acc){
    //ϵͳ�������û������ϲſ���ת��
    if(num<2){
        cout<<"�Բ���ϵͳ���������˻�����������ֱ��ת�ˣ�"<<endl;
        return;
    }
    if(acc.getMoney()==0){
        cout<<"�Բ����������㣬�޷�ת�ˣ�"<<endl;
        return;
    }
    while (true){
        cout<<"������Է��˻��Ŀ��ţ�"<<endl;
        string cardId;
        cin>>cardId;
//        Account account = getAccountBycardId(cardId,accounts);
//        if(account.getMoney()!=-1){
//            //�ж�ת�˶����Ƿ�Ϊ��¼��
//            if(!acc.getCardId().compare(cardId)){
//                cout<<"�����Ը��Լ�ת�ˣ�"<<endl;
        int flag = getIndexBycardId(cardId,accounts);
        //Account acc = getAccountBycardId(cardId,accounts);
        Account* account;
        if(flag!=-1){//�û��������
            if (!acc.getCardId().compare(cardId)) {
                cout<<"�����Ը��Լ�ת�ˣ�"<<endl;
                    }
            else{
                for (int i = 0; i < num; ++i) {
                    if(!accounts[i].getCardId().compare(cardId)){
                        account = &accounts[i];
                    }
                }
                //��ȷ�϶Է�����
                string name = "*" + account->getUserName().substr(1);
                cout<<"����ȷ��["<<name<<"]�����ϣ�"<<endl;
                string preName;
                cin>>preName;
                if(startsWith(account->getUserName(),preName)){
                    //��ʼת��
                    cout<<"������ת�˽��"<<endl;
                    double money;
                    cin>>money;
                    if(money>acc.getMoney()){
                        cout<<"�Բ����������㣬�����ת�ˣ�"<<acc.getMoney()<<"Ԫ"<<endl;
                    } else{
                        //����ת��
                        acc.setMoney(acc.getMoney()-money);
                        account->setMoney(account->getMoney()+money);
                        cout<<"ת�˳ɹ����Ѿ�Ϊ"<<account->getUserName()<<"ת��"
                            <<money<<"Ԫ"<<endl;
                       // cout<<account->getMoney();//debug
                        showAccount(acc);
                        return;
                    }
                } else{
                    cout<<"�Բ�������֤����"<<endl;
                }
            }
        } else{
            cout<<"�Բ����������ת�˿�������"<<endl;
        }
    }
}
static void drawMoney(Account &acc){
    cout<<"==================ȡ�����================"<<endl;
    while (true){
        //�ж��û�����Ƿ񳬹�100
        if(acc.getMoney()>=100){
            cout<<"��������ȡ����"<<endl;
            double money;
            cin>>money;
            if(money>acc.getQuotaMoney()){
                cout<<"������ȡ���ȡ���޶ÿ��������ȡ"<<acc.getQuotaMoney()<<"Ԫ"<<endl;
            } else{
                //���ж����
                if(acc.getMoney()>=money){
                    //����ȡǮ
                    acc.setMoney(acc.getMoney()-money);
                    cout<<"ȡǮ"<<money<<"�ɹ�,��ʣ:"<<acc.getMoney()<<"Ԫ"<<endl;
                    return;
                } else{
                    cout<<"���㣡"<<endl;
                }
            }
        } else{
            cout<<"�����˻�����100������ȡ�"<<endl;
            break;
        }
    }
}
static void depositMoney(Account &acc){
    cout<<"==================��Ǯ����================="<<endl;
    cout<<"�����������"<<endl;
    double money;
    cin>>money;
    acc.setMoney(acc.getMoney()+money);
    cout<<"������!"<<endl;
    showAccount(acc);
}
static void showAccount(Account &acc){
    cout<<"===================��ǰ�˻�����===================="<<endl;
    cout<<"���ţ�"<<acc.getCardId()<<endl;
    cout<<"������"<<acc.getUserName()<<endl;
    cout<<"��"<<acc.getMoney()<<endl;
    cout<<"�����޶"<<acc.getQuotaMoney()<<endl;
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
