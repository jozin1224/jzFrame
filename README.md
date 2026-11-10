# Why readme.md is in other language? (Brazilian)
Is hard to me  
just the comment in the code are in english
# jzFrame

## O que e?

Uma framework que eu fiz pra aprender sobre
* DLLs
* Controlar janelas
* e uma das primeira vez usando classes

## O que e possivel na jz?

ate o momento so da pra criar:  
* Bottoes
* Labels (Statics)
* HDC (e um pouco dificil)  

## O nome e inspirado na QT?
sim

## Como usa?
### Você NÃO deve usar a jz
Ela esta no inicio vale muito mais apenas usar a qt

### Agora e serio como usa?

#### criando a janela

```cpp
    JZwindow win; // create class
    win.init() // is many args just see in name of args
```
#### Adicionando um botão

```cpp
    win.add_button(L"SPAAAAAAAAAAAAAAAAAAAAAAAACEE", 10 /* X pos */, 10 /* Y pos */) // the other args is opcional
```

#### Adicionando um label (static)
``` cpp
win.add_label(L"SPAAAAAAAAAAAAAAAAAAAACEE", 10 /* X */, 10, /* Y */, 100, 100 /* SIZE */)
```



Feito por um ser não humano