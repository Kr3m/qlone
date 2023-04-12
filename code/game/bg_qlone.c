#include "g_local.h"
#include "bg_qlone.h"

// Allows to access an integer cvar
// thanx to Mr Pants "Excessive" mod
//int trap_Cvar_VariableIntegerValue(const char * var_name);
//const char *CG_ConfigString(int index);
int getCvarInt(const char * name) {
#ifdef CGAME
	return atoi(Info_ValueForKey(CG_ConfigString(CS_SERVERINFO), name));
#else
	return trap_Cvar_VariableIntegerValue(name);
#endif
}
