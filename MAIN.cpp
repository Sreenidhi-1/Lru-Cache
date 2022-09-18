#include<iostream>
#include<string.h>
#include<conio.h>
#include<map>
#define MAX 3
using namespace std;
struct node
{
public:
    int key;
    string value;
    struct node *fwd;
    struct node *bwd;
    node(int k,string v):key(k),value(v),fwd(NULL),bwd(NULL){}
};

class dll
{
    struct node *rear,*front;
public:
    dll()
    {
        front=NULL;
        rear=NULL;
    }
    //void create(int,string );
    node* insert_beg(int,string );
    bool isempty();
    void delete_end();
    int nodes();
    void move_front(node*);
    node *rear_node();
    void display();
};

bool dll::isempty()
{
      return rear == NULL;
}
/*void dll::create(int k,string a)
{
    struct node *n=new node(k,a);
    start=n;
}*/
node* dll::insert_beg(int k,string a)
{
    struct node *n=new node(k,a);
    if(!front && !rear)
    {
        front=rear=n;
    }
    else
    {
        n->fwd=front;
        front->bwd=n;
        front=n;
    }
    return n;
}

void dll::delete_end()
{
    if(isempty())
    {
        return;
    }
    if(front==rear)
    {
        delete rear;
        front=rear=NULL;
    }
    else
    {
        struct node *temp=rear;
        rear=rear->bwd;
        rear->fwd=NULL;
        delete temp;
    }
}

node* dll::rear_node()
{
    return rear;
}
void dll::move_front(struct node *n)
{
    if(n==front)
    {
        return;
    }
    if(n==rear)
    {
        rear=rear->bwd;
        rear->fwd=NULL;
    }
    else
    {
        n->bwd->fwd=n->fwd;
        n->fwd->bwd=n->bwd;
    }
    n->fwd=front;
    n->bwd=NULL;
    front->bwd=n;
    front=n;
}

class LRUCache
{
    int capacity;
    int size;
    dll *d;
    map<int,node*> m;
public:
    LRUCache(int c)
    {
        capacity=c;
        size=0;
        d=new dll();
        m=map<int,node*>();
    }
    void get(int);
    void put(int,string);
    void display();
    string most_recent();
    string least_recent();
    int key_value();
    ~LRUCache()
    {
        map<int,node*>::iterator i;
        for(i=m.begin();i!=m.end();i++)
        {
            delete i->second;
        }
        delete d;
    }
};
void LRUCache::get(int k)
{
    if(m.find(k)==m.end())
    {
        return;
    }
    string val=m[k]->value;
    d->move_front(m[k]);
    cout<<k<<"->"<<val<<endl;
}
void LRUCache::put(int k,string v)
{
    if(m.find(k)!=m.end())
    {
        m[k]->value=v;
        d->move_front(m[k]);
        return;
    }
    if(size==capacity)
    {
        int keys=d->rear_node()->key;
        m.erase(keys);
        d->delete_end();
        size--;
    }
    node *n=d->insert_beg(k,v);
    size++;
    m[k]=n;
}
void LRUCache::display()
{
    LRUCache cache(MAX);
    //map<int,node*>::iterator i;
    for (auto i = m.begin(); i != m.end();i++)
    {
        //cache.get(i->first);
        cout<<i->first<<" "<<i->second->value<<endl;
    }

    cout << endl;
}
string LRUCache::most_recent()
{
    /*map<int,node*>::iterator i;
    i=m.end();
    cout<<i->second->value;*/
    auto it=m.end();
    it--;
    string s=it->second->value;
    return s;
}
int LRUCache::key_value()
{
    //auto it;
    map<int,node*>::iterator it;
    return it->first;
}
string LRUCache::least_recent()
{
    for (auto i = m.begin(); i != m.end();i++)
    {
        //cache.get(i->first);
        return i->second->value;
        break;
    }
}

int main()
{
    int n,k[10],num,ki;
    string s[10];
    LRUCache cache(MAX);
    while(1)
    {
        cout<<"-----------------------------------------------"<<endl;
        cout<<"-----------------WEBSIT CACHE------------------"<<endl;
        cout<<"-----------------------------------------------"<<endl;
        cout<<"1.INSERT"<<endl<<"2.SERACH"<<endl<<"3.MOST RECENTLY USED WEBSITE"<<endl<<"4.LEAST RECENTLY USED WEBSITE"<<endl<<"5.DISPLAY"<<endl<<"6.EXIT";
        cout<<"ENTER YOUR CHOICE : ";
        cin>>n;
        if(n==1)
        {
            cout<<endl;
            cout<<"ENTER THE NUMBER OF WEBSITES : ";
            cin>>num;
            for(int i=0;i<num;i++)
            {
                cout<<"ENTER THE KEY : ";
                cin>>k[i];
                cout<<"ENTER THE WEBSITE TO BE SEARCHED : ";
                cin>>s[i];
                cache.put(k[i],s[i]);
            }
            /*for(int i=n;i<num;i++)
            {
                if(k[i]==key_value())
                {

                }
                else
                {

                }
            }*/
            cout<<"----THANK YOU FOR SERACHING-----"<<endl<<"-----------SEARCH AGAIN-----------"<<endl;
            getch();
            system("CLS");
        }
        else if(n==2)
        {
            cout<<endl;
            cout<<"ENTER THE KEY TO BE SEARCHED : ";
            cin>>ki;
            cache.get(ki);
            getch();
            //cout<<cache.key_value()<<endl;
            system("CLS");
        }
        else if(n==3)
        {
            cout<<endl;
            cout<<"MOST RECENTLY USED WEBSITE : "<<cache.most_recent()<<endl;
            getch();
            system("CLS");
        }
        else if(n==4)
        {
            cout<<endl;
            cout<<"LEAST RECENTLY USED WEBSITE : "<<cache.least_recent()<<endl;
            getch();
            system("CLS");
        }
        else if(n==5)
        {
            cout<<endl;
            cout<<"----------------------------"<<endl;
            cout<<"---------CACHE DATA---------"<<endl;
            cout<<"----------------------------"<<endl;
            cout<<endl;
            cache.display();
            getch();
            system("CLS");
        }
        else if(n==6)
            break;
    }
}
