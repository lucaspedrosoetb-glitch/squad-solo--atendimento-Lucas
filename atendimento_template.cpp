// ╔══════════════════════════════════════════════════════════════════════════╗
// ║  DESAFIO SQUAD — Sistema de Atendimento                                  ║
// ║  PSC II · Engenharia de Software · Campo Real · Prof. Giovane Galvão     ║
// ╠══════════════════════════════════════════════════════════════════════════╣
// ║  Compilar:  g++ -std=c++17 -Wall -o atendimento atendimento_template.cpp ║
// ║  Rodar:     ./atendimento                                                ║
// ╚══════════════════════════════════════════════════════════════════════════╝

#include <iostream>
#include <string>
using namespace std;

// ════════════════════════════════════════════════════════════════
// ESTRUTURA BASE — Nó genérico (NÃO MODIFIQUE)
// ════════════════════════════════════════════════════════════════
struct No {
    string nome;
    int    urgencia;   // 1=baixa, 2=media, 3=alta (usado apenas por Paciente)
    No*    prox;
    No(const string& n, int u = 0) : nome(n), urgencia(u), prox(nullptr) {}
};

// ════════════════════════════════════════════════════════════════
// R1 · FILA DE PACIENTES (estrutura FIFO com dois ponteiros)
// ════════════════════════════════════════════════════════════════
struct FilaPacientes {
    No* frente = nullptr;
    No* tras   = nullptr;

    // TODO 1: paciente entra no final da fila
    void enqueue(const string& nome, int urgencia) {
        No* novo = new No(nome, urgencia);
        if (tras == nullptr) {          // fila vazia
            frente = tras = novo;
        } else {
            tras->prox = novo;
            tras = novo;
        }
    }

    // TODO 2: remove e retorna o nome do paciente na frente
    string dequeue() {
        if (frente == nullptr) return "";
        No* tmp = frente;
        string nome = tmp->nome;
        frente = frente->prox;
        if (frente == nullptr) tras = nullptr;   // ficou vazia
        delete tmp;
        return nome;
    }

    // TODO 3: ver quem está na frente sem remover
    string frente_peek() const {
        if (frente == nullptr) return "";
        return frente->nome;
    }

    bool isEmpty() const { return frente == nullptr; }

    // BÔNUS: conta os nós na fila (iterativo)
    int tamanho() const {
        int cont = 0;
        for (const No* p = frente; p != nullptr; p = p->prox) cont++;
        return cont;
    }

    ~FilaPacientes() {
        while (!isEmpty()) dequeue();
    }
};

// ════════════════════════════════════════════════════════════════
// R2 · HISTÓRICO COM PILHA (estrutura LIFO)
// ════════════════════════════════════════════════════════════════
struct PilhaHistorico {
    No* topo = nullptr;

    // TODO 4: empilha um atendimento concluído
    void push(const string& nome) {
        No* novo = new No(nome);
        novo->prox = topo;
        topo = novo;
    }

    // TODO 5: desempilha e retorna o último atendimento
    string pop() {
        if (topo == nullptr) return "";
        No* tmp = topo;
        string nome = tmp->nome;
        topo = topo->prox;
        delete tmp;
        return nome;
    }

    // TODO 6: retorna o último atendimento SEM remover
    string peek() const {
        if (topo == nullptr) return "";
        return topo->nome;
    }

    bool isEmpty() const { return topo == nullptr; }

    ~PilhaHistorico() {
        while (!isEmpty()) pop();
    }
};

// ════════════════════════════════════════════════════════════════
// R3 · LISTA DE MÉDICOS DISPONÍVEIS (lista encadeada)
// ════════════════════════════════════════════════════════════════
struct ListaMedicos {
    No* head = nullptr;

    // TODO 7: adiciona um médico no final da lista
    void adicionarMedico(const string& nome) {
        No* novo = new No(nome);
        if (head == nullptr) {
            head = novo;
            return;
        }
        No* p = head;
        while (p->prox != nullptr) p = p->prox;
        p->prox = novo;
    }

    // TODO 8: remove e retorna o primeiro médico disponível
    string chamarMedico() {
        if (head == nullptr) return "";
        No* tmp = head;
        string nome = tmp->nome;
        head = head->prox;
        delete tmp;
        return nome;
    }

    // TODO 9: imprime todos os médicos disponíveis, com setas
    void percorrer(const string& prefixo = "") const {
        if (!prefixo.empty()) cout << prefixo << ": ";
        if (head == nullptr) {
            cout << "(lista vazia)\n";
            return;
        }
        for (const No* p = head; p != nullptr; p = p->prox) {
            cout << p->nome;
            if (p->prox != nullptr) cout << " -> ";
        }
        cout << "\n";
    }

    bool temMedico() const { return head != nullptr; }

    ~ListaMedicos() {
        while (head) {
            No* t = head;
            head  = head->prox;
            delete t;
        }
    }
};

// ════════════════════════════════════════════════════════════════
// R4 · RELATÓRIO E HISTÓRICO COMPLETO
// ════════════════════════════════════════════════════════════════

// TODO 10: imprime do topo à base SEM destruir o histórico
// Estratégia: desempilha de 'hist' imprimindo e empilhando em 'aux'
// (aux fica invertida); depois desempilha 'aux' de volta para 'hist',
// o que restaura a ordem original.
void imprimirHistorico(PilhaHistorico& hist) {
    cout << "\n=== Relatório de Atendimentos ===\n";
    if (hist.isEmpty()) {
        cout << "(nenhum atendimento registrado)\n";
        return;
    }

    PilhaHistorico aux;
    int n = 1;
    while (!hist.isEmpty()) {
        string item = hist.pop();
        cout << "  " << n++ << ". " << item << "\n";
        aux.push(item);
    }
    while (!aux.isEmpty()) {
        hist.push(aux.pop());
    }
}

// ════════════════════════════════════════════════════════════════
// PROGRAMA PRINCIPAL — integra as 4 estruturas
// ════════════════════════════════════════════════════════════════

int main() {
    cout << "╔═══════════════════════════════════════════════════╗\n";
    cout << "║  Sistema de Atendimento — Squad ________________  ║\n";
    cout << "╚═══════════════════════════════════════════════════╝\n\n";

    FilaPacientes  fila;
    PilhaHistorico historico;
    ListaMedicos   medicos;

    // ── Cadastrar médicos (R3) ────────────────────────────────
    medicos.adicionarMedico("Dra. Ana Lima");
    medicos.adicionarMedico("Dr. Bruno Costa");
    medicos.adicionarMedico("Dra. Carla Ramos");
    medicos.percorrer("Médicos disponíveis");

    // ── Pacientes chegam na fila (R1) ─────────────────────────
    cout << "\nPacientes chegando:\n";
    fila.enqueue("Eduardo (urgencia=3)", 3);
    fila.enqueue("Fernanda (urgencia=1)", 1);
    fila.enqueue("Gabriel (urgencia=2)", 2);
    fila.enqueue("Helena (urgencia=1)", 1);

    cout << "Próximo a ser atendido: " << fila.frente_peek() << "\n";
    cout << "Total na fila: " << fila.tamanho() << "\n";

    // ── Simulação de atendimentos ─────────────────────────────
    cout << "\nSimulação de atendimentos:\n";
    int atend = 1;
    while (!fila.isEmpty() && medicos.temMedico()) {
        string paciente = fila.dequeue();
        string medico   = medicos.chamarMedico();

        cout << "  [" << atend++ << "] " << medico
             << " atende " << paciente << "\n";

        // Registra no histórico (R2)
        historico.push(medico + " → " + paciente);

        // Médico volta para o final da lista depois de atender
        medicos.adicionarMedico(medico);
    }

    cout << "\n";
    medicos.percorrer("Médicos disponíveis ao final");

    // ── Último atendimento (peek na pilha) ────────────────────
    cout << "\nÚltimo atendimento registrado (peek): " << historico.peek() << "\n";

    // ── Relatório final (R4) ──────────────────────────────────
    imprimirHistorico(historico);

    // Prova de que o histórico não foi destruído
    cout << "\nTopo após o relatório (deve ser igual ao peek): "
         << historico.peek() << "\n";

    // ── Commit sugerido ──────────────────────────────────────
    cout << "\n💡 Lembrete de commits:\n";
    cout << "  git add atendimento_template.cpp README.md\n";
    cout << "  git commit -m \"feat: sistema de atendimento integrado (R1-R4)\"\n";
    cout << "  git push origin main\n";

    return 0;
}
