#include <iostream>  // cout, cin
#include <string>    // getline, tolower
#include <algorithm> // transform
#include <map>       // map
#include <vector>    // vector
#include <set>       // set


#define DEBUG_PRINT(x) do { std::cout << #x << ": " << x << '\n'; } while(false)
#define PR_ERR(x) do { std::cout << "[ERROR]: " << x << '\n'; } while(false)
#define PR(x) do { std::cout << x << '\n';} while(false)
#define IS_GLOBAL true


////////////////////////////////////////////////////////////////////////////////////////////
// Typedefs and Global Things, to be replaced with whatever.
// 
// Note: Having function callbacks makes this a bit more difficult to serialize,
// but if you have a form of global lookup that can be used with a string, you can then
// once again export the function name into a text document or something.
typedef std::string Role;
typedef std::string UserID;

// Note: implement case insensitivity in comparison operator since this may not be just a string.
typedef std::string RawCommand; 

// A default command function used with the command class.
class User;
typedef void(*CommandFunc)(const RawCommand &, User &);
namespace Commands
{
  void Default(const RawCommand &args, User &caller);
}



////////////////////////////////////////////////////////////////////////////////////////////
// User, Class
//
// The user class represents a single user in the system, who has a given set of roles.
// The purpose of the user class is to identify a specific user, and hold informaton on the 
// roles a partiuclar user fills. Additional information could be stored here as well.
class User
{
  // Only friends can touch your privates.
  friend class Command;

public:
  // Constructor(s)
  User(UserID id = "", std::set<Role> roles = { });

  // Role manipulation
  void RoleAdd(Role toAdd);
  void RoleRemove(const Role &toRemove);
  bool RoleHas(const Role &role) const;
  const UserID& IDGet() const;

private:
  // Variables, add tracked user data here...
  std::set<Role> _roles;
  UserID _id;
};




////////////////////////////////////////////////////////////////////////////////////////////
// Command, Class
//
// A single command holds information on the roles that are permitted to call it, and
// holds information on various other permissions. Note that this only resolves command
// permissions, but does not actually execute the comand. This is to allow for multiple
// commands to be mapped to the same function later.
class Command
{
public:
  // Constructor(s)
  Command(RawCommand command = RawCommand(), std::set<Role> roles = { }, bool isAllowedGlobally = false);

  // Operator overloading for comparisons. STL uses <
  bool operator<(const Command &rhs) const;
  bool operator==(const Command &rhs) const;
  operator const RawCommand&() const;

  // Role manipulation and Querying
  void RoleAllowedAdd(const Role &toAdd);
  void RoleAllowedRemove(const Role &toRemove);
  bool IsAllowedFor(const User &user) const;

  // Public Variables
  bool RoleAllowedGlobally;

private:
  // Private member funcs
  bool isAllowedFor(const Role &role) const;

  // Variables
  std::set<Role> _permittedRoles;
  RawCommand _rawCommand;
};




////////////////////////////////////////////////////////////////////////////////////////////
// CommandManager, Class
//
// Assoicates various commands with given users, and resolves persmissions for a given
// command when it's provided by a given user. Note: Does store users, and should only
// exist once. I did not make this a singleton because that may be a bit /too/ restrictive.
class CommandManager
{
public:
  // Constructor(s)
  CommandManager();

  // Command management
  void CommandAdd(const Command &command, CommandFunc cf = Commands::Default);
  void CommandRemove(const RawCommand &command);
  void CommandProcess(const RawCommand &command, User &user);
  void UserAdd(User user);
  void UserRemove(UserID user);
  User *UserGet(UserID id);

private:
  // Private variables
  std::map<UserID, User> _userLookup;
  std::map<RawCommand, Command> _commandLookup;
  std::map<Command, CommandFunc> _functionLookup;

  // Deletions. No comparisons or assignment/copy implemented for this for now, remove these if wanted.
  CommandManager(const CommandManager &rhs) = delete;
  CommandManager &operator=(const CommandManager &rhs) = delete;
  CommandManager &operator==(const CommandManager &rhs) = delete;
  CommandManager &operator!=(const CommandManager &rhs) = delete;
};




  /////////////////////////////////////
 // Global Function Implementations //
/////////////////////////////////////
// Command implementation, global functions and all.
namespace Commands
{
  void Default(const RawCommand &args, User &caller) { PR("Command behavior not set! Was provided with " << args); }
  void Hi(const RawCommand &args, User &caller) { PR("Hello to you too, " << caller.IDGet() << "!"); }
  void Ban(const RawCommand &args, User &caller) { PR(caller.IDGet() << " decided to ban themselves."); }
}

// Application entry point.
int main()
{
  // Build manager. Note: Good kind of thing to read from a file!
  CommandManager cm;
  cm.UserAdd({ "wisp",{ "user" }  });
  cm.UserAdd({ "weh" ,{ "admin" } });
  cm.CommandAdd({ "hello",{ "user", "admin" } }, Commands::Hi);
  cm.CommandAdd({ "hi"   ,{ "user", "admin" } }, Commands::Hi);
  cm.CommandAdd({ "hiya" ,{ "user", "admin" } }, Commands::Hi);
  cm.CommandAdd({ "hoi"  ,{ "admin" }         }, Commands::Hi);
  cm.CommandAdd({ "heya" ,{ "user", "admin" } }, Commands::Hi);
  cm.CommandAdd({ "default" ,{ "user", "admin" } });
  cm.CommandRemove("heya");

  while (true)
  {
    // Collect inputs
    std::string inName;
    std::string inCommand;
    std::cout << "Enter a name: ";
    getline(std::cin, inName);
    std::cout << "Enter a thing: ";
    getline(std::cin, inCommand);

    // Make lowercase
    std::transform(inName.begin(), inName.end(), inName.begin(), tolower);
    std::transform(inCommand.begin(), inCommand.end(), inCommand.begin(), tolower);

    // Call command
    cm.CommandProcess(inCommand, *cm.UserGet(inName));
  }

  return 1;
}


  //////////////////////////
 // User Imeplementation //
//////////////////////////
// Constructor(s)
User::User(UserID id, std::set<Role> roles)
  : _id(id)
  , _roles(roles)
{  }

// Role manipulation
void User::RoleAdd(Role toAdd)
{
  _roles.insert(toAdd);
}
void User::RoleRemove(const Role &toRemove)
{
  _roles.erase(toRemove);
}
bool User::RoleHas(const Role &role) const
{
  return _roles.find(role) != _roles.end();
}

const UserID &User::IDGet() const
{
  return _id;
}


  ////////////////////////////
 // Command Implementation //
////////////////////////////
// Command implementation, public.
Command::Command(RawCommand command, std::set<Role> roles, bool isAllowedGlobally)
  : RoleAllowedGlobally(isAllowedGlobally)
  , _rawCommand(command)
  , _permittedRoles(roles)
{  }

// Use the raw command to determine equivalence, not roles. 
bool Command::operator<(const Command &rhs) const
{
  if(this != &rhs)
    return _rawCommand < rhs._rawCommand;

  return false;
}

// Use the raw command to determine equivalence, not roles. 
bool Command::operator==(const Command &rhs) const
{
  if(this != &rhs)
    return _rawCommand == rhs._rawCommand;

  return true;
}

void Command::RoleAllowedAdd(const Role &toAdd)
{ 
  _permittedRoles.insert(toAdd); 
}

void Command::RoleAllowedRemove(const Role &toRemove)
{ 
  _permittedRoles.erase(toRemove);
}

bool Command::IsAllowedFor(const User &user) const
{
  for (auto & role : user._roles)
    if (!isAllowedFor(role))
      return false;

  return true;
}

// Command implementation, private.
bool Command::isAllowedFor(const Role &role) const
{ 
  return _permittedRoles.find(role) != _permittedRoles.end(); 
}

Command::operator const RawCommand&() const
{
  return _rawCommand;
}



  ////////////////////////////////////
 // Command Manager Implementation //
////////////////////////////////////
CommandManager::CommandManager()
  : _userLookup()
  , _commandLookup()
  , _functionLookup()
{  }

// Command management
void CommandManager::CommandAdd(const Command &command, CommandFunc cf)
{
  _commandLookup[command] = command;
  _functionLookup[command] = cf;
}

void CommandManager::CommandRemove(const RawCommand &command)
{
  _commandLookup.erase(command);
  _functionLookup.erase(command);
}

void CommandManager::CommandProcess(const RawCommand &command, User &user)
{
  auto commandIter = _commandLookup.find(command);

  if (commandIter != _commandLookup.end())
  {
    if (commandIter->second.IsAllowedFor(user))
    {
      auto functionIter = _functionLookup.find(command);

      if (functionIter != _functionLookup.end())
        functionIter->second(command, user);
      else
        PR_ERR("There should be a function mapped by default.");
    }
    else
      PR("This command is not allowed for this user!");
  }
  else
  PR("Could not find the command " << command << " anywhere!");
}

void CommandManager::UserAdd(User user)
{
  _userLookup[user.IDGet()] = user;
}

void CommandManager::UserRemove(UserID user)
{
  _userLookup.erase(user);
}

User *CommandManager::UserGet(UserID id)
{
  auto iter = _userLookup.find(id);
  if (iter != _userLookup.end())
    return &(iter->second);

  PR("The user with id " << id << " could not be found when looking them up!");
  return nullptr;
}
