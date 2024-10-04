#include <idc.idc>

static FuncDump(f, start)
{
    auto ea, str, teststr;
	
	ea = start;
	
	while( ea != BADADDR )
	{
	    str = GetFunctionName(ea);
		if( str != 0 )
		{
		    // Skip functions whose name is the generic sub_xxx()
			teststr = sprintf("sub_%X", ea);
			if( teststr != str )
			{
			    fprintf(f, "%s 0x%X\r\n", str, ea);
			}
		}
		
		ea = NextFunction(ea);
	}
}

static main()
{
    auto current = GetInputFile();
	current = AskFile(-1, current, "where should I write the symbols to?");
	if(current == 0)
	{
	    return -1;
	}
	auto f = fopen(current, "wb");
	Message("FuncDump: Start\n");
	
	FuncDump(f, 0x400000);
	Message("FuncDump: Done\n");
}