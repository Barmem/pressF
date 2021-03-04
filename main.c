#include <stdlib.h>

#include "test.h"

/**
 * Копирует содержимое памяти по адресу src в память dst.
 * Оба объекта dest и src рассматриваются как массив типов `unsigned char`.
 * Функция НЕ выделяет память.
 *
 * @param dest указатель на память КУДА копируем
 * @param src указатель на память ОТКУДА копируем
 * @param size количество байт, который надо скопировать из src в dest
 * @return копию указатель на dest
 */
char* memcpy_(void* dest, const void* src, unsigned int size) {
  // TODO: напиши меня!
  char* str = (char*)src;
  char* dek = (char*)dest;
  for (unsigned int i = 0; i < size; i++) {
    dek[i] = str[i];
  }
  return dest;
}

/**
 * Фильтрует массив объектов любого типа по условию.
 * Возвращает те элементы массива, которые удовлетворяют заданному условию.
 * Выделяет память для нового массива и копирует в него удовлетворяющие условию
 * элементы.
 *
 * @param src массив для фильтрации
 * @param count размер массива
 * @param size размер одного элемента, так как у нас нет типа: sizeof(some_type)
 * @param dest указатель на область памяти, куда должен быть записан результат
 * @param predicate указатель на функцию фильтрации
 * @return количество элементов в отфильтрованном массиве dest
 */
int filter(const void* src, int count, int size, void** dest,
           int (*predicate)(void*)) {
  int n = 0;  // Кол-во подходящих элементов
  char* str = (char*)src;
  for (int i = 0; i < count * size; i += size) {
    if (predicate((void*)&str[i]) == 1) n++;
  }  //Считаем n
  char* rez = (char*)malloc(n * size * sizeof(char));
  int index = 0;
  for (int i = 0; i < count * size; i += size) {
    if (predicate((void*)&str[i]) == 1) {
      memcpy_((void*)&rez[index], (void*)&str[i], size);
      index += size;
    }
  }
  *dest = (void*)rez;
  return n;
}

/**
 * Проверяет, является ли число чётным.
 *
 * @param n число на проверку
 * @return 1 если число четное, иначе 0.
 */
int is_even(void* n) {
  int num = *((int*)n);
  return num % 2 == 0;
}

/**
 * Проверяет, является ли строка палиндромом.
 *
 * @param str строка на проверку
 * @return 1 если число палиндром, иначе 0
 */


int is_palindrom(void* n) {
  char** pp = (char**)n;
  char* str = *pp;
  int k = 0;
  if (str == NULL) {
    return 0;
  }
  for (; *str != '\0'; str++, k++) {
  };
  for (unsigned int i = 0; i < k / 2; i++) {
    if (str[i] != str[k - i - 1]) return 0;
  }
  return 1;
}

void test(void) {
  // Это тесты. НЕ УДАЛЯЙТЕ ИХ!
  // Преподаватель будет грустить, если вы удалите тесты T_T.
  // Тесты проверяют, что ваш код работает правильно.
  // Если задача решена неправильно,
  // то в консоли вы увидите ошибку и пояснение.
  // Сдавайте лабу, когда устраните все ошибки в тестах.
  // Если возникли трудности, то попросите преподавателя вам помочь ^_^.

  {
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int* res;
    int n = filter((void*)arr, 10, sizeof(int), (void**)&res, is_even);
    ASSERT_INT(5, ==, n);
    for (int i = 0; i < n; i++) {
      ASSERT_TRUE(is_even(&arr[i]));
    }
    free(res);
  }
  {
    char* arr[] = {"aaaa", "abcd", "caac", " dd ", "eqws"};
    char** res;
    int n = filter((void*)arr, 1000, 5, (void**)&res, is_palindrom);
    ASSERT_INT(3, ==, n);
    ASSERT_STR_EQUAL("aaaa", res[0]);
    ASSERT_STR_EQUAL("caac", res[1]);
    ASSERT_STR_EQUAL(" dd ", res[2]);
    for (int i = 0; i < n; i++) {
      free(res[i]);
    }
    free(res);
  }
}

int main(void) {
  test();
  return 0;
}