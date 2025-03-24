#include <tc/tc_startup.h>
#include <tccore/aom.h>
#include <tccore/tctype.h>
#include <tccore/aom_prop.h>
#include <tccore/grm.h>
#include <tcinit/tcinit.h>
#include <sa/user.h>
#include <tc/folder.h>
#include <tccore/item.h>
#include <ae/dataset.h>
#include<bom/bom.h>
#include <qry/qry.h>

int ITK_user_main(int argc, char* argv[])
{
	int status = ITK_ok;
	char* user;
	char* password;
	char* group;
	char* itemId;

	user = ITK_ask_cli_argument("-u=");
	password = ITK_ask_cli_argument("-p=");
	group = ITK_ask_cli_argument("-g=");
	itemId = ITK_ask_cli_argument("-i=");

	status = ITK_init_module(user, password, group);

	//search asm and traverse it

	

	tag_t
		query = NULLTAG;

	status = QRY_find2("Item ID", &query);

	char
		** entries,
		** values;

	entries = (char**)MEM_alloc(sizeof(char**));
	entries[0] = (char*)MEM_alloc(sizeof(char*) * strlen("Item ID"));
	tc_strcpy(entries[0], "Item ID");

	values = (char**)MEM_alloc(sizeof(char**));
	values[0] = (char*)MEM_alloc(sizeof(char*) * strlen(itemId));
	tc_strcpy(values[0], itemId);

	int num_found = 0;
	tag_t* items = NULL;

	status = QRY_execute(query, 1, entries, values, &num_found, &items);

	if (entries[0])
		MEM_free(entries[0]);

	if (entries)
		MEM_free(entries);

	if (values[0])
		MEM_free(values[0]);

	if (values)
		MEM_free(values);

	tag_t
		itemrev = NULLTAG;

	//Get the Item Revision

	status = ITEM_ask_latest_rev(items[0], &itemrev);
	

	tag_t
		bomwindow = NULLTAG,
		
		* children = NULL;

	status=BOM_create_window(&bomwindow);

	get_all_child_lines(tag_t currentLine);

	status = BOM_set_window_top_line(bomwindow, items[0], itemrev, NULLTAG, &top_bom_line);

	

	status = ITK_exit_module(true);

	return status;
}

int get_all_child_lines(tag_t currentLine)
{
	int iFail = ITK_ok;
	int noOfChildLines=0;
	tag_t*
		chilLines = NULL;
	iFail = BOM_line_ask_all_child_lines(currentLine, &noOfChildLines, &chilLines);

	for (int i =0; i < noOfChildLines; i++)
	{

	}
	return iFail;
}