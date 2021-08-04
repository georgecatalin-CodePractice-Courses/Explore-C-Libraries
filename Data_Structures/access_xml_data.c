#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <libxml/parser.h>

int main(int argc, char **argv)
{
	const char filename[]="02_03-sample1.xml";
	
	//declare the libxml2 variables to be used for parsing its contents
	xmlDocPtr doc;
	xmlNodePtr node;
	
	//open the xml document for parsing
	doc=xmlParseFile(filename);
	
	if(doc ==NULL)
	{
		fprintf(stderr,"Unable to parse the file %s. \n",filename);
		perror("Parse error");
		exit(1);
	}
	
	//fetch the root element
	node=xmlDocGetRootElement(doc);
	
	if(node==NULL)
	{
		fprintf(stderr,"The document %s is empty. Error number is  %i. \n",filename, errno);
		perror("Fetch root element");
		
		xmlFreeDoc(doc); //release the doc pointer
		exit(1);
	}
	
	printf("The root node is %s. \n", node->name);
	
	//cleanup
	xmlFreeDoc(doc);
	
	return 0;
}
