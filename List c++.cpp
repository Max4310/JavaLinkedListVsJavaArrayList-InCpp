#include <iostream>
using namespace std;


template <typename T>
T sum(T a, T b) {
	return a + b;
}


template <typename T>
struct nodo
{
	T info;
	nodo* next;
}; //str nodo sulla quale vado a basare la logica della likedlist


template <typename T>
class LinkedList {
private :
	nodo <T>* testa; //riferimento alla testa
	nodo <T>* last; //riferimento all'ultimo elemento
	int size; //dimensione della lista
	bool empty;

public:
	LinkedList(){ //costruttore
		testa = nullptr; //NULL
		last = nullptr;
		size = 0;
		empty = true;
	}

	void addLast(T element) { //aggiungo un elemento in coda
		if (testa == nullptr) {
			testa = new nodo<T>(); //se la lista è vuota creo un nuovo nodo alla testa
			testa->info = element;
			testa->next = nullptr;
			last = testa;
		}
		else {
			last->next = new nodo<T>(); //altrimenti ne creo uno dalla coda 
			last = last->next;

			last->info = element;
			last->next = nullptr;
		}

		size++; //aumento la size
		empty = false;
	}

	void addFirst(T element) { //aggiungo un elemento in testa
		if (testa == nullptr) {
			testa = new nodo<T>(); //se la testa è vuota aggiugo un elemento semplicemente facendoci puntare la testa
			testa->info = element;
			testa->next = nullptr;
			last = testa;
		}
		else {
			nodo<T>* s = new nodo<T>(); //se la lista non è vuota creo un puntatore di appoggio dove vado ad istanzaire il futuro primo elemento 
			
			s->info = element;
			s->next = testa;

			testa = s; //collego la testa all'attuale primo elemento
		}

		size++; //aumenmto la size
		empty = false;
	}

	T getFirst() {
		if (testa != nullptr) {
			return testa->info;
		}

		throw invalid_argument("the list is empty"); //creo un eccezione se la lista è vuota perche nn posso ritornare null essendo che T potrebbe rappresentare un tipo primitivo
		//non posso nenache ritornare un valre tipo -1 perche nn so di che tipo sarebbe quindi mi creo l'eccezione
	}

	T getLast() {
		if (last != nullptr) {
			return last	->info;
		}

		throw invalid_argument("the list is empty"); //stesso discorso per l'eccezione
	}

	int getSize() {
		return size; //ritorno la size
	}

	void removeFirst() {
		if (testa != nullptr) { //gestisco questo if per evtiare errori di esecuzione del codice (se la testa punta a null testa->next allora restituirà un errore)
			testa = testa->next;

			size--;
			if (size == 0) {
				empty = true;
			}
		}
	}

	void removeLast() {
		nodo <T>* cursore = testa;

		if (cursore != nullptr) { //stessa logica dell if sopra 
			if (cursore->next != nullptr) {

				while (cursore->next->next != nullptr) { //raggiungo il penultimo elemento
					cursore = cursore->next;
				}

				last = cursore;
				cursore->next = nullptr; 
				size--;
			}
			else {
				testa = nullptr; //se sto qui allora ho solo un elemento perche testa -> next == null 
				last = nullptr;

				size--;
			}
		}

		if (size == 0) {
			empty = true;
		}
	}
	
	T get(int index) {
		if (index < 0 || index > size || empty) {
			throw invalid_argument("index is too big or too small"); //stessa logica per le eccezioni 
		}
		

		nodo<T>* c = testa;
		int i = 0;

		while (i<index) { //ciclo tutta la lista fino a index 

			if (c->next != nullptr) {
				c = c->next;
				i++;
			}
			else {
				throw invalid_argument("index is too big");
			}
		}

		return c->info; //restituisco l'utimo
	}
	
	void clear() {
		testa = nullptr;
		last = nullptr;
		empty = true;
	}
};

template <typename T>
class ArrayList {
private:
	T* insideArray; //in questo puntatore ci andro a salvarare l'array interno
	int size; //creo un size ovvero il valore massimo di elementi nell'array attualmente allocato
	int lastIndex; //l'ultimo indice che indica se è stato preso
	bool empty; //verifica se è vuoto o meno
public:
	ArrayList() { //costruttore inizializzo l'array a max 5 elementi perche mi è comodo
		size = 5;
		lastIndex = 0;
		insideArray = new T[size];
		empty = true;
	}

	void add(T elements) { // il metodo che aggiunge un elemento
		empty = false;
		if (lastIndex < size) { //verifico se posso inserire l'elemento nell'array attualmente istanziato
			insideArray[lastIndex] = elements;
			lastIndex++;
		}
		else { //se non posso aggiungo di nuovo 5 elementi 
			size += 5;
			T* x = new T[size]; //reistazio un nuovo array piu grande 

			for (int i = 0; i < lastIndex; i++) {
				x[i] = insideArray[i];
			} //copio il vecchio array in quello nuovo
			 
			x[lastIndex] = elements; //aggiungo l'elemento 
			insideArray = x; //aggiorno l'attributo
			lastIndex++; //aggiorno last index
		}
	}

	T get(int index) {
		if (index > lastIndex || index < 0 || empty) { //stesso discorso delle eccezioni della linked
			throw invalid_argument("index is too big or too small");
		}

		return insideArray[index];
	}

	int getSize() {
		return lastIndex;
	}

	void clear() {
		size = 5;
		lastIndex = 0;
		insideArray = new T[size];
		empty = true;
	}

};

int main()
{
	ArrayList<int> arrayList;

	arrayList.add(5);
	arrayList.add(6);
	arrayList.add(7);
	arrayList.add(8);
	arrayList.add(9);
	arrayList.add(10); //criticità perche deve andare a riallocare l'array




	/* output attesi 
	* 5
	* 6
	* 7
	* 8
	* 9
	* 10
	*/
	for (int i = 0; i < arrayList.getSize();i++) { //vado a stampare la lista
		cout << "ARRAYLIST "<<i + 1 << ": " << arrayList.get(i) << endl;
	}

	arrayList.clear(); //svuoto la lista

	try {
		int a = arrayList.get(0);
		//criticità a zero con la lista vuota... ma tutto sembra funzionare perche va in eccezione! 
	}
	catch (invalid_argument& e) { //gestisco l'eccezione
		cout << "errore" << endl;
	}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------




	LinkedList<int> linkedlist;

	linkedlist.addLast(1);
	linkedlist.addLast(2);
	
	/* output attesi
	* 1 
	* 2
	*/

	for (int i = 0; i < linkedlist.getSize(); i++) {
		cout << "LIKENDLIST INSERIMENTO CODA " << i + 1 << ": " << linkedlist.get(i) << endl;
	}


	linkedlist.addFirst(3);
	linkedlist.addFirst(4);

	/*output attesi
	* 4
	* 3
	* 1
	* 2
	*/

	for (int i = 0; i < linkedlist.getSize(); i++) {
		cout << "LIKENDLIST INSERIMENTO TESTA " << i + 1 << ": " << linkedlist.get(i) << endl;
	}


	/*output attesi
	* first : 4 
	* last : 2 
	*/

	cout << "LINKEDLIST PRIMO ELEMENTO: " << linkedlist.getFirst() << " LINKEDLIST ULTIMO ELEMENTO: " << linkedlist.getLast() << endl;

	linkedlist.removeFirst();
	linkedlist.removeLast();


	/*output attesi
	* first : 3
	* last : 1
	*/

	cout << "LINKEDLIST PRIMO ELEMENTO dopo rimozione: " << linkedlist.getFirst() << " LINKEDLIST ULTIMO ELEMENTO dopo rimozione: " << linkedlist.getLast() << endl;

	linkedlist.clear();

	try {
		int a = linkedlist.get(0);
		//criticità a zero con la lista vuota... ma tutto sembra funzionare perche va in eccezione!
	}
	catch (invalid_argument& e) { //gestisco l'eccezione
		cout << "errore" << endl;
	}


	try {
		int a = linkedlist.getFirst();
		//va in eccezione essendo vuota!
	}
	catch (invalid_argument& e) { //gestisco l'eccezione
		cout << "errore" << endl;
	}

	try {
		int a = linkedlist.getLast();
		//va in eccezione essendo vuota!
	}
	catch (invalid_argument& e) { //gestisco l'eccezione
		cout << "errore" << endl;
	}

}