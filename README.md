# Manager de portofoliu la GigiQuant

Acest proiect a fost dezvoltat în cadrul cursului de **Proiectarea Algoritmilor**, la **Facultatea de Automatica și Calculatoare**, domeniul **AIASI**, anul universitar 2025-2026. 

Scopul aplicației este de a dezvolta algoritmi pentru a rezolva diferite probleme din domeniul financiar:
* calculul **indicatorul Sharpe Ratio**
* identificarea oportunităților de **arbitraj**
* **optimizarea** de portofoliu
* determinarea **probabilității** că o acțiune să aibă un preț după un număr de zile

---

## Structura Proiectului

* 'src/': Conține codurile sursa( '.c' și '.h' ).
* 'în/': Seturile de date de intrare pentru testare.
* 'ref/': Fișierele de referință pentru verificarea corectitudinii.
* 'Makefile': Scriptul pentru compilarea și gestionarea proiectului.
* 'config.json' / 'tests.json': Fișierele necesare rulării checker-ului.
* 'ProiectPA_GigiQ.pdf': Pdf-ul ce conține cerințele.

---

### Structuri de Date si Algoritmi Utilizati

Pentru implementarea eficienta a modulelor financiare, am utilizat urmatoarele:
* **Liste inlantuite**
* **Stive / Cozi**
* **Arbori binari**
* **Grafuri orientate si liste de adiacenta**
* **Structuri personalizate ('struct')**

---

#### Cum se instalează și rulează

1. Se download-eaza directory-ul.
2. Se instleaza [checker-ul](https://gitlab.cs.pub.ro/paaa/checker/-/releases)-Linux AMD64 Binary și se adaugă în folderul salvat.
3. Se deschide un terminal ( este nevoie de [WSL](https://learn.microsoft.com/en-us/windows/wsl/install) ) și se navighează până în folderul proiectului.
4. Se instalează valgrind și cppcheck ( sudo apt install valgrind, sudo apt install cppcheck) și se oferă drept de execuție checker -ului: chmod +x ./nume checker.
5. Se rulează checker-ul ./nume checker.