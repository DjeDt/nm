--- FT_NM

```

1:	void *ptr = mmap(binary)
2:	struct mach_header_64 *header = ptr;
3:	struct load_command_64 *load_command = (struct load_command_64*)header;

load_command->cmd == LC_SEGMENT_64 ?
	4.1:	struct segment_command_64 *segment = (struct segment_command_64*)load_command;
	4.2:	struct section_64* section = (struct section_64*)segment + sizeof(*segment);
	4.3:	next_section = section + sizeof(*section);

load_command->cmd == LC_SYMTAB ?
	4.1:	struct symtab_command *symbol = (struct symtab_command*)load_command;
	4.2:	struct nlist_64 *elem = (struct nlist_64*)header + symbol->symoff;
	4.3:	extract_data from symbol_list

5:	next_load_command = load_command  + load_command->cmdsize;
	go to 4.

```

# Schema

```
 -----------------------------------------------------------------------
|																 		|
|	header																|
|																 		|
|	 ------------------------------------------------------------		|
|	|							|					|			 |		|
|	|	load_command			|	load_command	|	...	 	 |		|
|	|							|					|	 	 	 |		|
|	|	 ---------------------------------------------------	 |		|
|	|	|													|	 |		|
|	|	|	segment											|	 |		|
|	|	|													|	 |		|
|	|	|	 ------------------------------------------- 	|	 |		|
|	|	|	|		    |			 |			 |		|	|	 |		|
|	|	|	|  section  |  section	 |	section  | ...	|	|	 |		|
|	|	|	|		    |			 |			 |		|	|	 |		|
|	|	|	|		    |			 |			 |		|	|	 |		|
|	|	|	|		    |			 |			 |		|	|	 |		|
|	|	|	 -------------------------------------------	|	 |		|
|	|	|													|	 |		|
|	|	 ---------------------------------------------------	 |		|
|	|														 	 |		|
|	 ------------------------------------------------------------		|
|															 	 		|
 -----------------------------------------------------------------------
```