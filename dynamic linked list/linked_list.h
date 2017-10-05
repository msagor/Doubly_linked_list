
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_



	void Init(int M, int C);

	void Destroy();

	int Insert (int x, char* value_ptr, int value_len);

	void Delete(int x);

	char * Lookup (int x);

	void PrintList();


#endif 
