/* COMIENZO DE DESCRIPCION

	__USE_WIKI__

	Funciones para generar trees y btrees a partir de strings con 
	descripciones de estos árboles en notación lisp. Funcionan para
	cualquier tipo de dato que pueda leerse desde un istream con >>.

	FIN DE DESCRIPCION */

// Son copias de los algoritmo lisp2tree y list2btree originales 
// de util_tree.h y util_btree.h, pero que delegan la conversion 
// de de std::string a T al operator>>(istream,T)... 
// entonces se hace generico y funciona para cualquier tipo de 
// dato al que se le pueda hacer un cin>>d;


#include <iostream>
#include <sstream>
#include "tree.hpp"
#include "btree.hpp"

namespace aed {
	
	template<typename T>
	bool lisp2tree(std::stringstream &ss, aed::tree<T> &t, typename aed::tree<T>::iterator it) {
		char aux;
		std::streampos pos = ss.tellg();
		while (ss>>aux) {
			if (aux == ')') {
				return true;
			} else {
				if (aux!='(') ss.seekg(pos);
				T data; if (!(ss>>data)) return false;
				it = t.insert(it, data);
				if (aux=='(') if (!lisp2tree(ss, t, it.lchild())) return false;
				++ it;
			}
			pos = ss.tellg();
		}
		return true;
	}
	
	
	template<typename T>
	bool lisp2tree(std::string s, aed::tree<T> &t) {
		assert(t.begin()==t.end());
		for(size_t i=0;i<s.size();i++) { // insertar espacios para que al leer strings no tome los ")" por estar pegados a las claves
			if(s[i]==')') s.insert(i++," ");
		}
		std::stringstream ss; ss<<s;
		return lisp2tree(ss,t,t.begin());
	}
	
	template<typename T>
	aed::tree<T> lisp2tree(std::string s) {
		aed::tree<T> t;
		lisp2tree(s,t);
		return t;
	}
	
	
	
	template<typename T>
	bool lisp2btree(std::stringstream &ss, aed::btree<T> &t, typename aed::btree<T>::iterator it, char nullchar) {
		char aux;
		std::streampos pos = ss.tellg();
		int nchild = 0;
		while (ss>>aux) {
			if (aux == ')') {
				return true;
			} else if (aux==nullchar) {
				if (++nchild==3) return false;
			} else {
				if (aux!='(') ss.seekg(pos);
				T data; if (!(ss>>data)) return false;
				if (nchild==0) {
					t.insert(it.left(), data);
					if (aux=='(') lisp2btree(ss, t, it.left(),nullchar);
				} else if (nchild==1) {
					t.insert(it.right(), data);
					if (aux=='(') lisp2btree(ss, t, it.right(),nullchar);
				} else return false;
				++nchild;
			}
			pos = ss.tellg();
		}
		return true;
	}
	
	
	template<typename T>
	bool lisp2btree(std::string s, aed::btree<T> &t, char nullchar='.') {
		assert(t.begin()==t.end());
		for(size_t i=0;i<s.size();i++) { // insertar espacios para que al leer strings no tome los ")" por estar pegados a las claves
			if(s[i]==')') s.insert(i++," ");
		}
		std::stringstream ss; ss<<s;
		char aux; T data; if (!(ss>>aux>>data)||aux!='(') return false;
		t.insert(t.begin(),data);
		return lisp2btree(ss,t,t.begin(),nullchar);
	}
	
	template<typename T>
	aed::btree<T> lisp2btree(std::string s, char nullchar='.') {
		aed::btree<T> t;
		lisp2btree(s,t,nullchar);
		return t;
	}
	
	
} // aed

