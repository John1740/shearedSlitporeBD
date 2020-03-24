#ifndef COMMAND_H
#define COMMAND_H

template<class SYSTEM_T>
class COMMAND
{
public:
   virtual void doForSystem ( SYSTEM_T& sysIn ) = 0;
};

#endif // COMMAND_H
