//--------------------------------- NGUYEN MAU HAM ---------------------------------
IDRandom* Tao_IDNode(int ID);
IDRandom* Tao_MIN_MAX(IDRandom*& first, int MIN, int MAX); //Call this function when the program starts
void Them_ID(IDRandom*& first, int ID); //Call this function when read FileDSCauHoi.txt
void Xoa_ID(IDRandom*& first, int ID); //Call this function when delete a question
int Random(int Min, int Max); //Get a random number between Min and Max
int Cap_ID(IDRandom* first); //Call this function when create an ID for a question

//--------------------------------- DINH NGHIA HAM ---------------------------------
IDRandom* Tao_IDNode(int ID) {
	IDRandom* Node = new IDRandom;
	Node->ID = ID;
	Node->next = nullptr;
	return Node;
}

IDRandom* Tao_MIN_MAX(IDRandom*& first, int MIN, int MAX) {
	first = Tao_IDNode(MIN - 1);
	first->next = Tao_IDNode(MAX + 1);
	return first;
}

void Them_ID(IDRandom*& first, int ID) {
	IDRandom* ptr = first;
	while (ptr->next->ID < ID) ptr = ptr->next;
	IDRandom* Node = Tao_IDNode(ID);
	Node->next = ptr->next;
	ptr->next = Node;
}

void Xoa_ID(IDRandom*& first, int ID) {
	IDRandom* ptr = first;
	while (ptr->next->ID != ID) ptr = ptr->next;
	IDRandom* tmp = ptr->next;
	ptr->next = tmp->next;
	delete tmp;
}

int Random(int Min, int Max) {
	return Min + rand() % (Max + 1 - Min);
}

int Cap_ID(IDRandom* first) {
	IDRandom* ptr = first;
	while (ptr->next != nullptr && ptr->next->ID - ptr->ID == 1) ptr = ptr->next;
	if (ptr->next == nullptr) {
		return 0; //The list is full. Can't add more
	}
	else {
		int ID = Random(ptr->ID + 1, ptr->next->ID - 1);
		Them_ID(first, ID);
		return ID;
	}
}
