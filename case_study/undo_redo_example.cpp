#include <stack>
#include <iostream>
#include <memory>

// ----- the Command Interface -----
class ICommand // abstract base class
{
public:
    virtual void execute() = 0; // pure virtual function
    virtual void undo() = 0;
    virtual void redo() = 0;
};


// ----- the MODEL -----
class Tv
{
    // member m变量类型_名
    bool mOn;
    int mChannel;

public:
    Tv() {}
    // 改 set
    void switchOn() { mOn = true; }
    void switchOff() { mOn = false; }
    void switchChannel(int channel)
    {
        mChannel = channel;
    }
    // 查 get
    bool isOn() { return mOn; }
    int getChannel() { return mChannel; }
};


// ----- concrete ICommand commands -----
class TvOnCommand : public ICommand
{
    Tv *mTv; // type? pointer to Tv

public:
    TvOnCommand(Tv &tv) : mTv(&tv) {}

    void execute() { mTv->switchOn(); }
    void undo() { mTv->switchOff(); }
    void redo() { mTv->switchOn(); }
};

class TvOffCommand : public ICommand
{
    TvOnCommand mTvOnCommand; // reuse complementary command
public:
    TvOffCommand(Tv &tv) : mTvOnCommand(tv) {}
    void execute() { mTvOnCommand.undo(); } // to off
    void undo() { mTvOnCommand.execute(); } // to on
    void redo() { mTvOnCommand.undo(); }    // to off
};



class TvSwitchChannelCommand : public ICommand
{
    Tv *mTv; // type? pointer to Tv
    int mOldChannel;
    int mNewChannel;

public:
    TvSwitchChannelCommand(Tv *tv, int channel)
    {
        mTv = tv;
        mNewChannel = channel;
    }

    void execute()
    {
        mOldChannel = mTv->getChannel(); // get 1
        mTv->switchChannel(mNewChannel); // set 2
    }

    void undo()
    {
        mTv->switchChannel(mOldChannel); // 1
    }

    void redo()
    {
        mTv->switchChannel(mNewChannel); // 2
    }
};



// ----- our CONTROLLER with undo/redo -----
typedef std::stack<std::shared_ptr<ICommand>> commandStack_t;
// 给std::stack<std::shared_ptr<ICommand>> 取一个别名 叫做commandStack_t

// container: elements with the same type
// array vector matrix tensor
// matrix<double>

// std::stack<std::shared_ptr<ICommand>>
// container:   std::stack 栈
// element type: std::shared_ptr<ICommand> smart pointer to ICommand (ICommand*)

class CommandManager
{
    commandStack_t mUndoStack; // type? commandStack_t? std::stack<std::shared_ptr<ICommand>>
    commandStack_t mRedoStack;

public:
    CommandManager() {}

    void executeCmd(std::shared_ptr<ICommand> command)
    {
        mRedoStack = commandStack_t(); // clear the redo stack
        // int a = int(); // 调用int的构造函数 无参调用
        // int a = int(1); // 调用int的构造函数 传入1
        command->execute();
        mUndoStack.push(command);
    }

    void undo()
    {
        if (mUndoStack.size() <= 0)
        {
            return;
        }
        mUndoStack.top()->undo();          // undo most recently executed command
        mRedoStack.push(mUndoStack.top()); // add undone command to undo stack
        mUndoStack.pop();                  // remove top entry from undo stack
    }

    void redo()
    {
        if (mRedoStack.size() <= 0)
        {
            return;
        }
        mRedoStack.top()->redo();          // redo most recently executed command
        mUndoStack.push(mRedoStack.top()); // add undone command to redo stack
        mRedoStack.pop();                  // remove top entry from redo stack
    }
};

int main()
{
    // using namespace std;

    Tv tv; // type Tv; name tv
    CommandManager commandManager;

    int *p_int = new int(5.0); // 申请一片大小为int的内存，初始化为5，把地址作为返回值
    int a;                     // 申请一片大小为int的内存
    p_int = &a;

    // create command for switching to channel 1
    // std::shared_ptr<int> pint = new int; // smart ptr to int; int*
    // int* --> smart ptr to int
    // std::shared_ptr<int> pint(new int);

    // new TvSwitchChannelCommand(&tv, 1) type? TvSwitchChannelCommand*
    // std::shared_ptr<TvSwitchChannelCommand> c1(new TvSwitchChannelCommand(&tv, 1));
    std::shared_ptr<ICommand> c1(new TvSwitchChannelCommand(&tv, 1));
    commandManager.executeCmd(c1);
    std::cout << "switched to channel " << tv.getChannel() << std::endl; // see out

    std::shared_ptr<ICommand> c2(new TvSwitchChannelCommand(&tv, 2)); // create command for switching to channel 2
    commandManager.executeCmd(c2);
    std::cout << "switched to channel: " << tv.getChannel() << std::endl;

    std::shared_ptr<ICommand> c3(new TvSwitchChannelCommand(&tv, 3)); // create command for switching to channel 3
    commandManager.executeCmd(c3);
    std::cout << "switched to channel: " << tv.getChannel() << std::endl;

    std::cout << "undoing..." << std::endl;
    commandManager.undo();
    std::cout << "current channel: " << tv.getChannel() << std::endl;

    std::cout << "undoing..." << std::endl;
    commandManager.undo();
    std::cout << "current channel: " << tv.getChannel() << std::endl;

    std::cout << "redoing..." << std::endl;
    commandManager.redo();
    std::cout << "current channel: " << tv.getChannel() << std::endl;

    std::cout << "redoing..." << std::endl;
    commandManager.redo();
    std::cout << "current channel: " << tv.getChannel() << std::endl;

    return 0;
}