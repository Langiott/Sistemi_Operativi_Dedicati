# Sistemi_Operativi_Dedicati
In questo corso abbiamo creato e gestito processi o task , programmazione conocrrente, mutex, semafori e scheduling , esercitandoci con script c++

##PROGRAMMA:
Ecco un raccoglimento degli argomenti che hai fornito:

### 1. **Programmazione Concomitante**  
   - **Principi e Indeterminismo**  
   - **Analisi dei Programmi Concomitanti**  
     - Sezione critica per 2 processi: Algoritmo di Decker
     - Verifica della correttezza
     - Logica temporale lineare
     - Model Checker
     - Algoritmo del fornaio
   - **Semafori**
   
### 2. **PTHREADS**
   - **Descrizione e Gestione dei Threads**  
   - **Schedulazione dei Threads sotto Linux**  
   - **Gestione del Tempo sotto Linux**
   - **Gestione Threads Periodici**
   - **Mutua Esclusione**
   
### 3. **Sezione Critica nei Sistemi Distribuiti**
   - **Assenza di Memoria Condivisa**
   - **Coordinamento mediante Messaggi**
     - Messaggistica periodica
     - Saturazione del buffer di memoria
     - Buffers ciclici asincroni
   - **Algoritmi di Coordinamento**
     - Coordinatore centrale
     - Ricart-Agrawala: Algoritmo basato su messaggio e su token

### 4. **Agent-Oriented Programming (AOP) e Sistemi Multi-Agente**
   - **IEEE Standard FIPA**  
   - **Java Agent DEvelopment Framework (JADE)**
     - Agenti e Behaviours
     - Scheduling dei Behaviours
     - OneShotBehaviour, CyclicBehaviour, WakerBehaviour, TickerBehaviour
   - **AOP e IoT (Internet of Things)**
   - **Protocollo di Trasmissione MQTT**

### 5. **Schedulazione dei Processi in Tempo Reale**  
   - **Sistemi Embedded e Smart Objects**  
   - **Real-Time Systems e RTOS**
   - **Sorgenti di Indeterminismo**  
   - **Modeling Real-Time Activities**  
     - Task, Processor States, Schedule
     - Real-time tasks: Periodic, Aperiodic, Sporadic Tasks
     - Predictability vs. Efficiency
     - Timing, Precedence e Resource Constraints
     - Scheduling Anomalies
     
### 6. **Real-Time Scheduling**
   - **Schedulazione per Task Aperiodici**
     - Earliest Due Date, Earliest Deadline First (EDF)
     - Bratley's Algorithm, Spring, Latest Deadline First, EDF*
   - **Schedulazione per Task Periodici**
     - Proportional Share Algorithm
     - Timeline (Cyclic) Scheduling
     - Priority Scheduling, Rate Monotonic (RM)
     - Utilization Upper Bound, Hyperbolic Bound
     - Deadline Monotonic, Response Time Analysis
     - EDF with D ≤ T e Processor Demand Criterion
   - **Schedulazione per Hybrid Task Sets**
     - Aperiodic Servers: Polling Server (PS), Deferrable Server (DS), Sporadic Server (SS)
     - Total Bandwidth Server (TBS), TBS*, Tunable Bandwidth Server
     - Constant Bandwidth Server (CBS)
     
### 7. **Gestione delle Risorse Condivise**
   - Problemi di **Mutual Exclusion** e Sezioni Critiche
   - **Priority Inversion**
   - **Protocolli per la Mutua Esclusione**:
     - Non Preemptive Protocol (NPP)
     - Highest Locker Priority (HLP)
     - Priority Inheritance Protocol (PIP)
     - Priority Ceiling Protocol (PCP)
     - Stack Resource Policy (SRP)

### 8. **Panoramica sugli RTOS (Real-Time Operating Systems)**
   - **Standards per RTOS**
     - RT-POSIX, OSEK/VDX, AUTOSAR, ARINC 653
     - μ-ITRON, TOPPERS
   - **RTOS Commerciali**
     - VxWorks, OSE, QNX
   - **RTOS Linux-Related**
     - RTLINUX, RTAI, Xenomai
   - **RTOS Open Source**
     - ERIKA ENTERPRISE

### 9. **Linux Kernel**  
   - **Compilazione e Configurazione del Kernel Linux**
   - **Generalità sui Moduli del Kernel Linux**
     - Compilazione di nuovi componenti
     - Scrittura di moduli
     - Caricamento e rimozione dei moduli
     - Parametri e interfacciamento dei moduli
     - Importazione ed esportazione dei simboli
   - **Debugging del Kernel e File System /proc**
   - **Stati di un Processo e Gestione del Tempo**
   - **Tasklets e Preemption del Kernel**
   - **Schedulazione dei Processi in Linux**
   - **I/O e Implementazione di un Driver Semplice**

Adesso puoi trascrivere questo contenuto in Markdown!
