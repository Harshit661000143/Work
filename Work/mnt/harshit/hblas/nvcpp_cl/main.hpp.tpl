[+ autogen5 template +]
/*
 * Application [+NormalName+]
 * Copyright (C) [+Author+] [+(shell "date +%Y")+] <[+Email+]>
 * 
[+CASE (get "License") +]
[+ == "BSD"  +][+(bsd  (get "Name") (get "Author") " * ")+]
[+ == "LGPL" +][+(lgpl (get "Name") (get "Author") " * ")+]
[+ == "GPL"  +][+(gpl  (get "Name")                " * ")+]
[+ESAC+] */


#ifndef [+NameHUpper+]_H_
#define [+NameHUpper+]_H_


#endif  /* #ifndef [+NameHUpper+]_H_ */
