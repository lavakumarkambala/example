#include <stdio.h>
#include<tccore/custom.h>
#include<conio.h>
#include<tcinit/tcinit.h>
#include<epm/epm.h>
#include<tccore/aom_prop.h>
#include<common/emh_const.h>
#include<tccore/item_msg.h>

#define DMSLAPI __declspec(dllexport)
extern "C"
{
	//__declspec(dllexport) int linDMSL_register_callbacks();
	DMSLAPI int linDMSL_register_callbacks();

}

int registerDMSLExtensions(int* decision, va_list args);
EPM_decision_t dmslCheckTargetCount   (EPM_rule_message_t msg);