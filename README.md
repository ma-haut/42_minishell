# 🐚 Minishell - Un shell Unix en C

## 📝 Description
Recréation d'un shell basique similaire à bash, développé dans le cadre du cursus 42. 
Ce projet reproduit les fonctionnalités essentielles d'un interpreteur de commandes Unix.

## ✨ Fonctionnalités implémentées
- ✅ Exécution de commandes avec recherche dans le PATH
- ✅ Redirections (`>`, `>>`, `<`)
- ✅ Pipes (`|`) pour chaîner les commandes
- ✅ Operateurs logiques `&&` et `||`
- ✅ Variables d'environnement (`$VAR`)
- ✅ Gestion des signaux (Ctrl+C, Ctrl+D, Ctrl+\)
- ✅ Builtins : `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- ✅ Gestion des quotes simples et doubles
- ✅ Historique des commandes

## 💡 Défis techniques rencontrés
- Parsing complexe : Gestion des quotes, variables d'environnement et caractères spéciaux
- Gestion mémoire : Prévention des fuites mémoire avec des structures complexes
- Processus : Implémentation correcte des pipes et redirections avec fork/exec
- Signaux : Gestion appropriée des signaux dans différents contextes

## 📊 Résultat
✅ Note finale : 116/100
✅ Tests : Tous les tests obligatoires passés
✅ Norminette : Code conforme aux standards 42
