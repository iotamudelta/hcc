// Copyright (c) Microsoft
// All rights reserved
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
// THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
// See the Apache Version 2.0 License for specific language governing permissions and limitations under the License.
/// <tags>P2</tags>
/// <summary>
/// array/array_view of short_view_type
/// </summary>

#include <amp_short_vectors.h>
#include <amptest.h>
#include <amptest_main.h>

using namespace concurrency;
using namespace concurrency::graphics;
using namespace Concurrency::Test;

template<typename T>
void test_container() restrict(amp)
{
    T local_array;
    array_view<T, 1> arr_view(1, &local_array);
}


template<typename T>
void test_container() restrict(cpu)
{
    array<T, 1> arr(1);
}

runall_result test() restrict(cpu,amp)
{
    test_container<int_2>();
    test_container<int_4>();
    test_container<uint_2>();
    test_container<uint_4>();

    test_container<float_2>();
    test_container<float_4>();

    //compilation should succeed
    return runall_pass;
}

runall_result test_main()
{
	accelerator_view av = require_device(device_flags::NOT_SPECIFIED).get_default_view();

	runall_result result;
    result &= test();
	result &= GPU_INVOKE(av, runall_result, test);
	return result;
}
