#include"lockauto.h"
LockAuto::LockAuto(Lock *lock)
{
        this->lock=lock;
        lock->enter();

}
LockAuto::~LockAuto()
{
        lock->leave();
}

