# Formal_languages_2022/Earley algorithm
This is my implementation of Earley algorithm
Code coverage:

![earley_cov](https://user-images.githubusercontent.com/79002842/206210396-69f49b07-35ff-4b76-a1bf-49431bf73f0d.jpg)

Для запуска программы воспользуйтесь скриптом main.sh . Когда будете запускать, надо помнить, что должно быть хотя бы одно начальное правило с нетерминалом `S`, а также пустое слово означает '#'. Идея алгоритма заключается в построении множеств ситуаций, которые получаются при помощи таких функций, как Scan, Predict и Complete - они описаны в файле `Earley.cpp`. Асимптотика Scan - $O(\|w\|^{2} \cdot \|G\|)$, где w - слово, G - грамматика$. Асимптотика Predict - $O(\|w\|^{2} \cdot \|G\|^{2})$. Асимптотика Complete - $O(\|w\|^{3} \cdot \|G\|^{2})
