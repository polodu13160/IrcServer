# IrcServer

``` mermaid
flowchart TD
    subgraph Client_Side
        C[Client IRC]
    end

    subgraph Server_Logic
        A[Socket Listener] -->|Accept| B[Client Handler]
        B -->|Signal SIGINT/SIGQUIT| S[Cleanup & Shutdown]
        B -->|Commandes| D{Parsing}
        D -->|NICK/USER| E[Authentification]
        D -->|JOIN| F[Gestion des Channels]
        D -->|PRIVMSG| G[Relai Messages]
    end

    C <-->|Protocol TCP| A
```






nos sources :
https://www.codequoi.com/envoyer-et-intercepter-un-signal-en-c/

https://www.undernet.org/docs/irc-quit-message-faq

https://modern.ircdocs.horse/#rpltopicwhotime-333

https://mathieu-lemoine.developpez.com/tutoriels/irc/protocole/?page=generalites



