#include "RegisterDMSLExtensions.hxx"

#define MULTIPLE_IRS_SELECTION 919050

#define CHECK_ERROR(X) if(X!=ITK_OK) {char *error = NULL; EMH_ask_error_text(X,&error); printf("%S", error); TC_write_syslog(error); if(error) MEM_free(error);}

 int libDMSL_register_callbacks()

{
	printf("DMSL Library Loaded");
	//This function registers a custom exit(custom function poiner)
	//for a given user specified action function

	CUSTOM_register_exit("libDMSL", "User_init_module", (CUSTOM_EXIT_ftn_t) registerDMSLExtensions);

	return 0;
}
 int registerDMSLExtensions(int* decision, va_list args)
 {
	 // Register WF
	 int iFail;
	 iFail = EPM_register_rule_handler("DMSL-Check-Target-Object-Count","This handler check the count of target Item Revision",
		( EPM_rule_handler_t )	dmslCheckTargetCount);
	 //MM C

	 //RunTim
	 return iFail;
 }
 EPM_decision_t dmslCheckTargetCount(EPM_rule_message_t msg)
 {
	 EPM_decision_t decision = EPM_go;;

	 tag_t currentTask = msg.task;

	 int status = ITK_ok;
	 tag_t
		 root_task = NULLTAG;
	 CHECK_ERROR( EPM_ask_root_task(currentTask, &root_task));

	 int count = 0;

	 tag_t
		 * attachments = NULL,
	 class_id = NULLTAG;
	 char
		 * class_name = NULL;
	 int targetIRCount=0;
	 CHECK_ERROR(EPM_ask_attachments(root_task, EPM_target_attachment,&count, &attachments));

	 for (int i = 0; i < count; i++)
	 {
		 CHECK_ERROR(POM_class_of_instance(attachments[i], &class_id));
		 CHECK_ERROR( POM_name_of_class(class_id, &class_name));

		 if (~tc_strcmp(class_name,"ItemRevision")==0)
		 {
			 targetIRCount++;
		 }
		 if (targetIRCount > 1)
		 {
			 decision = EPM_nogo;
			 char* errorText = NULL;
			
			 status = EMH_ask_error_text(MULTIPLE_IRS_SELECTION, &errorText);
			 status = EMH_store_error_s1(EMH_severity_error, MULTIPLE_IRS_SELECTION, errorText);

			 TC_write_syslog(errorText);

			 if (errorText)
				 MEM_free(errorText);
			 break;
		 }
	 }
	 if (attachments)
		 MEM_free(attachments);

	 if (class_name)
		 MEM_free(class_name);


	 return decision;
 }