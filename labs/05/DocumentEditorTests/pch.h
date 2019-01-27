// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here

#endif //PCH_H
#define BOOST_TEST_INCLUDED
#pragma warning (push, 3)
#pragma warning (disable:4456 4702)
#include <boost/test/unit_test.hpp>
#pragma warning (pop)

#include <boost/range/algorithm/copy.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>

#include <boost/algorithm/string/replace.hpp>
#include <boost/test/output/compiler_log_formatter.hpp>
