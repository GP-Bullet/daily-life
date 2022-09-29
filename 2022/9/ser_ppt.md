    Json数据格式的服务器与客户端传输信息或者交互接口
用户存
用户名
密码
好友名
密保问题和答案
命令
时间
群
封装好类

    class usr
    {
    public:
        long long id;
        int fd;
        string friendname;
        int friendid;
        string name;
        string pwd;
        int status;
        string question;
        string answer;
        string choice;
        string mes_fri;
        time_t time;
        string group;
        vector<string> box;
        string buf;
        string filename;
    };
    
    class Friend
    {   public:
        vector<string> myfri;
        vector<string> request;
        string from;
        string to;
        vector<string> buf;
        vector<int> time;
        map<string,int> ship;

    };

    class Fri_chat
    {
        public:
         vector<string> history;
         vector<string>unread;
         vector<time_t> time;
         vector<time_t> unread_t;
         vector<string> file;

    };
    class Group
    {   public:
        string owner;
        vector<string> manager;
        vector<string> member;
        vector<string> join_req;
        vector<string> history;
        vector<time_t> time;
    };
    class myGroup
    {
        public:
        vector<string> mygroup;
        map<string,int>status;
       
    };
    class Gro_chat
    {
        public:
        vector<string> unread_mes;
        vector<time_t> unread_t;
        vector<string> filename;
    };
     class mymessage
    {   public:
        vector<string> mes;
    };




能相互聊天的原理