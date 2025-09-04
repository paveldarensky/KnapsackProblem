# Lab 4 — Knapsack Problem

🇷🇺 Четвёртая лабораторная работа по дисциплине **«Алгоритмы и структуры данных»**.  
Задача: реализовать три подхода к решению **задачи о рюкзаке** (Knapsack Problem) и сравнить их эффективность.  

🇬🇧 Fourth lab work for the course **“Algorithms and Data Structures”**.  
Task: implement three approaches to solving the **Knapsack Problem** and compare their efficiency.  

---

## 📋 Условие / Task

Дано `n` предметов с весами `w1,…,wn` и стоимостями `c1,…,cn`.  
Имеется рюкзак грузоподъёмностью `W`. Нужно найти **максимальную суммарную стоимость** предметов, которые можно в него поместить.  

Методы:  
1. **Жадный алгоритм / Greedy**  
   - выбирается предмет с максимальным отношением `цена/вес`, который помещается в рюкзак.  

2. **Бэктрекинг с отсечениями / Backtracking with pruning**  
   - полный перебор с возвратом, исключая заведомо невозможные решения.  
   - используется только при `n ≤ 30`.  

3. **Динамическое программирование / Dynamic Programming**  
   - построение таблицы `A[k][w]`, где `k` — число предметов, `w` — вместимость рюкзака.  

---

## 🛠 Реализация / Implementation

- Структура `cargo { weight, cost }` описывает груз.  
- Случайные веса и стоимости генерируются автоматически.  
- Грузоподъёмность рюкзака выбирается как:  
W = (w1 + w2 + ... + wn) / 2

- Три функции реализуют разные подходы:  
- `greedy()`  
- `backtracking()`  
- `dynamic_programming()`  

---

🎯 Цель работы / Purpose

🇷🇺 Изучение и сравнение различных подходов к решению задач дискретной оптимизации. Практическая реализация жадных алгоритмов, перебора с отсечениями и динамического программирования.

🇬🇧 Study and comparison of different approaches to discrete optimization. Practical implementation of greedy algorithms, backtracking with pruning, and dynamic programming.
