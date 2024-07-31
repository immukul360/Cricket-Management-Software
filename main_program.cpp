#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
int main();
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
int LinearSearch(vector<string> row, string search_data){
    int i;
    for(int i=0; i<row.size();i++){
        if(row[i]==search_data){
            return i;
        }
    }
    return -1;
}
class Player{
    string name;
    string player_id;
    string role;
    string cap="N"; // N for Normal Player, C for captain, VC for vice captain
    string status="Active";
    string jersey_number;
    public:
    Player(string name, string role, string jersey_number, string player_id){
        this->name=name;
        this->role=role;
        this->jersey_number=jersey_number;
        this->player_id=player_id;
    }
    void adddetailstofile(){
        ofstream outfile("player_records.csv", ios::app);
        outfile << name << "," << role << ","<<cap<<","<<status<<","<<jersey_number<<","<<player_id<<endl;
        outfile.close();
    }
    void Player_Status(string status){
        this->status=status;
    }
    void showdetails(){
    cout<<"\033[33m"<<name<<"\033[0m"<<"(";
    cout<<role<<") \t Status: "<<status<<" \tJersey Number: "<<jersey_number;
    cout<<" \tPlayer ID: "<<player_id<<endl;       
    }

    ~Player(){}
};
class Team{
    string team_id;
    string team_password;
    public:
    string name;
    Team(string name, string team_id, string team_password){
        this->name=name;
        this->team_id=team_id;
        this->team_password=team_password;
    }
    void adddetailstofile()
    {

        ofstream outfile("team_user.csv", ios::app);
        outfile << name << "," <<team_id << ","<<team_password<<endl;
        outfile.close();
    }
    void showdetails(){
        cout<<"\033[33m"<<name<<"\033[0m"<<" ID:"<<team_id<<"\tPassword:"<<team_password<<endl;       
    }
    ~Team(){}
};
class fixture {
    string TeamA;
    string TeamB;
    string date;
    string time;
    string day;
    string stadium_name;
    public:
    fixture(string TeamA, string TeamB, string date, string time, string day, string stadium_name){
        this->TeamA=TeamA;
        this->TeamB=TeamB;
        this->date=date;
        this->time=time;
        this->day=day;
        this->stadium_name=stadium_name;
    }
    void adddetailstofile()
    {

        ofstream outfile("Fixtures.csv", ios::app);
        outfile << TeamA << "," << TeamB << ","<<date<<","<<time<<","<<day<<","<<stadium_name<<endl;
        outfile.close();

    }
    void showdetails(){
       cout<<"\033[34m"<<TeamA<<" vs "<<TeamB<<"\033[0m"<< " on "<<date<<"("<<day<<")"<<" at "<<stadium_name<<endl;
    }
    ~fixture(){}
};
class Stadium {
    string name;
    string capacity;
    string stadium_id;
    string city;
    string state; 
    string Hotel1;
    string Hotel2;
    public:
    Stadium(string name, string capacity, string stadium_id,string city, string state, string Hotel1, string Hotel2){
        this->name=name;
        this->capacity=capacity;
        this->city=city;
        this->state=state;
        this->Hotel1=Hotel1;
        this->Hotel2=Hotel2;
        this->stadium_id=stadium_id;
    }
    void adddetailstofile()
    {
        ofstream outfile("Stadium_List.csv", ios::app);
        outfile << name << "," << capacity << "," << stadium_id << ","<<city<<","<<state<<","<<Hotel1<<","<<Hotel2<<endl;
        outfile.close();
    }
    
    void showdetails(){
        cout<<"\033[34m"<<name<<"\033[0m";
        cout<<"\tCapacity:"<<capacity;
        cout<<"\tState:"<<state;
        cout<<"\tCity:"<<city;
        cout<<"\tStadium ID:"<<stadium_id;
        cout<<"\tTeam A Hotel:"<<Hotel1<<"\tTeam B Hotel:"<<Hotel2<<endl;    
    }
    ~Stadium(){     
    }
};
void showUpcomingMatches(string team_id){
        ifstream infile("fixtures.csv");
        string line;
        while (getline(infile, line)) {
            stringstream s(line);
            string cell;
            vector<string> row;
            while (getline(s, cell, ',')) 
                row.push_back(cell);
            if(row[0]==team_id || row[1]==team_id){
                fixture fixture_1(row[0],row[1],row[2],row[3],row[4],row[5]);
                fixture_1.showdetails();
            }
        } 
        infile.close();
        return;
}
vector<string> PlayingXIAndSquadFetcher(string team_id, string file_name){
    ifstream infile(file_name,ios::in);
    string line;
    while (getline(infile, line)) {
        stringstream lineStream(line);
        string cell;
        vector<string> row;
        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        if(row[0]==team_id){
            infile.close();
            return row;
        } 
    }
    infile.close(); 
    return {"-1"};
}
void showPlayerDetails(vector<string> player_list){
        ifstream infile("player_records.csv");
        string line;
        while (getline(infile, line)) {
            stringstream s(line);
            string cell;
            vector<string> row;
            while (getline(s, cell, ',')) 
                row.push_back(cell);
            if(LinearSearch(player_list,row[5])!=-1){
                Player player_1(row[0],row[1],row[4],row[5]);
                player_1.showdetails();
            }
        } 
        infile.close();
        return;
}
void modifyDetailsInTeams(string file_name,string team_id)
    {
        clearInputBuffer();
        string current_player, new_player;
        cout<<"Please enter the Player ID for player to be removed : ";
        getline(cin,current_player);
        cout<<"Please enter the Player ID for new player: ";
        getline(cin,new_player);
        vector<string> lines;
        ifstream infile(file_name);
        string line;
        while (getline(infile, line)) {
            lines.push_back(line);
        } 
        infile.close();
        ofstream outfile(file_name, ios::out);
        for(int i=0; i<lines.size();i++){
            stringstream s(lines[i]);
            string cell;
            vector<string> row;
            while (getline(s, cell, ',')) {
                row.push_back(cell);
            }
            if(row[0]!=team_id || (LinearSearch(row,current_player)==-1)){
                outfile<<lines[i]<<endl;
            }
            else{
                int index=LinearSearch(row,current_player);
                row[index]=new_player;
                for(int j=0; j<row.size();j++){
                    outfile<<row[j];
                    if(j==row.size()-1) outfile<<endl;
                    else outfile<<",";
                }
            }
        }
        outfile.close();
    }
class PlayingXI{
    vector<string> player_list;
    public:
    PlayingXI(vector<string> player_list)
    {
        this->player_list=player_list;
    }
    void adddetailstofile()
    {

        ofstream outfile("PlayingXI.csv", ios::app);
        for(auto it=player_list.begin(); it<player_list.end(); it++){
            outfile<<*it;
            if(it!=player_list.end()-1) outfile<<",";
            else outfile<<endl;
        }
        outfile.close();
    }
    void showdetails(){
        showPlayerDetails(player_list);
    }
    ~PlayingXI(){}

};
class squad{
    vector<string> player_list;
    public:
    squad(vector<string> player_list)
    {
        this->player_list=player_list;
    }
    void adddetailstofile()
    {

        ofstream outfile("Squad.csv", ios::app);
        for(auto it=player_list.begin(); it<player_list.end(); it++){
            outfile<<*it;
            if(it!=player_list.end()-1) outfile<<",";
            else outfile<<endl;
        }
        outfile.close();
    }
    void showdetails(){
        showPlayerDetails(player_list);
        }
    ~squad(){}
};
void showPlayers(){
    ifstream infile("player_records.csv");
    string line;
    while (getline(infile, line)) {
        stringstream s(line);
        string cell;
        vector<string> row;
        while (getline(s, cell, ',')) 
            row.push_back(cell);
        Player player_1(row[0],row[1],row[4],row[5]);
        player_1.showdetails();
    } 
    infile.close();  
}
void showVenues(){
    ifstream infile("Stadium.csv");
    string line;
    while (getline(infile, line)) {
        stringstream s(line);
        string cell;
        vector<string> row;
        while (getline(s, cell, ',')) 
            row.push_back(cell);
        Stadium stadium_1(row[0],row[1],row[2],row[3],row[4],row[5],row[6]);
        stadium_1.showdetails();
    } 
    infile.close();
}
void showTeams(){
    ifstream infile("team_user.csv");
    string line;
    while (getline(infile, line)) {
        stringstream s(line);
        string cell;
        vector<string> row;
        while (getline(s, cell, ',')) 
            row.push_back(cell);
        Team team_1(row[0],row[1],row[2]);
        team_1.showdetails();
    } 
    infile.close();
}
void showMatches(){
        ifstream infile("fixtures.csv");
        string line;
        while (getline(infile, line)) {
            stringstream s(line);
            string cell;
            vector<string> row;
            while (getline(s, cell, ',')) 
                row.push_back(cell);
            fixture fixture_1(row[0],row[1],row[2],row[3],row[4],row[5]);
            fixture_1.showdetails();

        } 
        infile.close();
}
void addTeam(){
    clearInputBuffer();
    string team_id;
    string team_password;
    string name;
    cout<<"Please enter name of the team: ";
    getline(cin,name);
    cout<<"Please enter team_id: ";
    getline(cin,team_id);
    cout<<"Please enter team_password: ";
    getline(cin,team_password);
    Team team_1(name, team_id, team_password);
    team_1.adddetailstofile();
}
void addPlayer(){
    clearInputBuffer();
    string name;
    string player_id;
    string role;
    string jersey_number;
    cout<<"Please enter name of the Player: ";
    getline(cin,name);
    cout<<"Please enter player id: ";
    getline(cin,player_id);
    cout<<"Please enter role: ";
    getline(cin,role);
    cout<<"Please enter jersey_number: ";
    getline(cin,jersey_number);
    Player player_1(name, role, jersey_number, player_id);
    player_1.adddetailstofile();

}
void addVenue(){
    clearInputBuffer();
    string name;
    string capacity;
    string stadium_id;
    string city;
    string state; 
    string Hotel1;
    string Hotel2;  
    cout<<"Please enter Name of the stadium: ";
    getline(cin,name); 
    cout<<"Please enter Capacity of the team: : ";
    getline(cin,capacity);
    cout<<"Please enter Stadium_id: ";
    getline(cin, stadium_id);
    cout<<"Please enter City of the team: : ";
    getline(cin,city);
    cout<<"Please enter State of the team: : ";
    getline(cin,state);
    cout<<"Please enter Hotel Name for Team A: ";
    getline(cin,Hotel1);
    cout<<"Please enter Hotel Name for Team B: ";
    getline(cin,Hotel2);
    Stadium Stadium_1(name, capacity, stadium_id,city, state, Hotel1,Hotel2);
    Stadium_1.adddetailstofile();
}
void addMatch(){ 
    clearInputBuffer();
    string TeamA;
    string TeamB;
    string date;
    string time;
    string day;
    string stadium_name;
    cout<<"Please enter Team A Name: ";
    getline(cin,TeamA);
    cout<<"Please enter Team B Name: ";
    getline(cin,TeamB);
    cout<<"Please enter match date in DDMMYYYY Format: ";
    getline(cin,date);
    cout<<"Please enter match time in HH:MM Format: ";
    getline(cin,time);
    cout<<"Please enter the stadium Name: ";
    getline(cin,stadium_name);
    fixture fixture_1(TeamA, TeamB, date, time, day, stadium_name);
    fixture_1.adddetailstofile();
}
class admin_user{
    string name;
    string password;
    public:
    admin_user(string name, string team_password){
        this->name=name;
        this->password=team_password;
    }
    ~admin_user(){}
};
void teamLoginMenu(string login_id){
    vector<string> team_details;
    ifstream infile("team_user.csv");
    string line;
    while (getline(infile, line)) {
        stringstream lineStream(line);
        string cell;
        vector<string> row;
        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        if(row[1]==login_id){
            team_details=row;
            break;
        }
    } 
    Team current_team(team_details[0],team_details[1],team_details[2]);
    infile.close();
    int n;
    vector<string> player_list_1, player_list_2;
    while(1){
        system("cls");
        cout<<"\033[33mNamaste "<<current_team.name<<"! Welcome to Men's Cricket World cup 2023 \033[0m \n";
        cout<<"Press 1 to view the squad\n";
        cout<<"Press 2 to view the Playing XI\n";
        cout<<"Press 3 to change the Playing XI\n";
        cout<<"Press 4 to view matches list and related details\n";
        cout<<"Press 5 to view all venues\n";
        cout<<"Press 0 for main menu\n";
        cout<<"\033[32mEnter a choice: \033[0m";
        cin>>n;
        system("cls");
        switch(n){
            case 1:
            player_list_1 = PlayingXIAndSquadFetcher(login_id,"Squad.csv");
            showPlayerDetails(player_list_1);
            cout<<"Press any key to continue!";
            getch();
            break;
            case 2: 
            player_list_2 = PlayingXIAndSquadFetcher(login_id,"PlayingXI.csv");
            showPlayerDetails(player_list_2);
            cout<<"Press any key to continue!";
            getch();
            break;
            case 3:
            modifyDetailsInTeams("PlayingXI.csv",login_id); 
            cout<<"Modification Successfull!";
            cout<<"\nPress any key to continue!";
            getch();
            break;
            case 4:
            showUpcomingMatches(login_id);
            cout<<"Press any key to continue!";
            getch();
            break;
            case 5:
            showVenues();
            cout<<"Press any key to continue!";
            getch();
            break;
            case 0: main();
            break;
            default:cout<<"Invalid input";
            cout<<"Press any key to continue!";
            getch();
        }
    }
}
void adminLoginMenu(){
    int n;
    while(1){
        system("cls");
        cout<<"\033[33mHi Admin! Welcome to Men's Cricket World cup 2023 Management System \033[0m  \n";
        cout<<"Press 1 to view the list of Players\n";
        cout<<"Press 2 to view the list of venues\n";
        cout<<"Press 3 to view the list of teams\n";
        cout<<"Press 4 to view the list of matches\n";   
        cout<<"Press 5 to add a player\n"; 
        cout<<"Press 6 to add a team\n";
        cout<<"Press 7 to add a venue\n";
        cout<<"Press 8 to schedule a match\n";
        cout<<"Press 0 for main menu\n";
        cout<<"\033[32mEnter a choice: \033[0m";
        cin>>n;
        system("cls");
        switch(n){
            case 1: showPlayers();
            cout<<"Press any key to continue!";
            getch();
            break;
            case 2: showVenues();
            cout<<"Press any key to continue!";
            getch();
            break;
            case 3: showTeams(); 
            cout<<"Press any key to continue!";
            getch();
            break;
            case 4: showMatches();
            cout<<"Press any key to continue!";
            getch();
            break;
            case 5: addPlayer();
            cout<<"Player is successfully added\n";
            cout<<"Press any key to continue!";
            getch();
            break;
            case 6: addTeam();
            cout<<"Team is successfully added\n";
            cout<<"Press any key to continue!";
            getch();
            break;
            case 7: addVenue();
            cout<<"Venue is successfully added\n";
            cout<<"Press any key to continue!";
            getch();
            break;
            case 8: addMatch();
            cout<<"Match is successfully added\n";
            cout<<"Press any key to continue!";
            getch();
            break;
            case 0: main();
            break;
            default:cout<<"Invalid input";
        }
    }
}
bool adminLoginverifier(string login_id, string password){
    ifstream infile("admin_user.csv");
    string line;
    bool found = 0;
    while (getline(infile, line)) {
        stringstream lineStream(line);
        string cell;
        vector<string> row;
        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        if(row[0]==login_id && row[1]==password){
            found=1;
            break;
        } 
    } 
    infile.close();
    return found;  
}
bool teamLoginverifier(string login_id, string password){
    ifstream infile("team_user.csv");
    string line;
    bool found = 0;
    while (getline(infile, line)) {
        stringstream lineStream(line);
        string cell;
        vector<string> row;
        while (getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        if(row[1]==login_id && row[2]==password){
            found=1;
            break;
        }
    } 
    infile.close();
    return found;  
}
void team_login(){
    clearInputBuffer();
    string login_id, password;
    while(1){
    system("cls");
    cout<<"Enter Team Login ID: ";
    getline(cin,login_id);
    cout<<"Enter Password: ";
    getline(cin,password);
    if(teamLoginverifier(login_id,password)){
        teamLoginMenu(login_id);
    }    
    else{
        cout<<"Invalid Credentials! Press try again\nPress any key to continue!";
        getch();
        main();
    }

    }
   
}
void admin_login(){
    clearInputBuffer();
    string login_id, password;
    while(1){
    system("cls");
    cout<<"Enter admin Login ID: ";
    getline(cin,login_id);
    cout<<"Enter Password: ";
    getline(cin,password);
    if(adminLoginverifier(login_id,password)){
            adminLoginMenu();
    }    
    else{
        cout<<"Invalid Credentials! Press try again\nPress any key to continue!";
        getch();
        main();
    }

    }

}
int main(){
    system("cls");
    int n;
    cout<<"\033[33m*****Cricket World Cup 2023 Management System******\033[0m\n";
    cout<<"Press 1 for Admin Login\n";
    cout<<"Press 2 for Team Login\n";
    cout<<"Press 0 for exit\n";
    cout<<"\033[32mEnter a choice: \033[0m";
    while(1){
        cin>>n;
        switch(n){
            case 1: admin_login();
            break;
            case 2: team_login();
            break;
            case 0: cout<<"Bye!!";
            exit(1);
            break;
            default:cout<<"Invalid input, please enter 0, 1 or 2: ";
        }
    }
    return 0;

}