#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <errno.h>

int main(int argc, char **argv)
{
	const char filename[]="02_02-sample1.xml";

	//declare libxml2 variable
	xmlDocPtr doc;

	//parse the xml document
	doc=xmlParseFile(filename);
	if(doc==NULL)
	{
		fprintf(stderr,"Unable to parse the document named \t %s due to error number %i.\n",filename,errno);
		perror("Parse document");
	        exit(1);
        }

	//get information from the prolog of the xml file
	if (doc->version!=NULL && doc->encoding!=NULL)
	{
		printf("The file named %s  has the XML Version \t %s and the XML encoding \t %s.\n", filename, doc->version, doc->encoding);
	}
	else
	{
		printf("The file lacks either XML Version information or encoding information.\n");
	}

	xmlFreeDoc(doc);

	return 0;
}
