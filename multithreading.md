```cpp
import std;

bool isPrime(size_t n, size_t i = 2)
{
	if(n <= 2)
		return (n == 2) ? true : false;
	if(n % i == 0)
		return false;
	if(i * i > n)
		return true;
	return isPrime(n, i + 1);
}

size_t single(const std::vector<size_t>& v)
{
	return std::count_if(v.begin(), v.end(), [](const auto &el)
	{
		return isPrime(el);
	});
}

size_t block(const std::vector<size_t>& v, size_t n_threads)
{
	std::vector<size_t> res(n_threads);
	std::vector<std::thread> threads(n_threads);

	auto lambda = [&v, &res](size_t a, size_t b, size_t th_id)
	{
		res[th_id] = std::count_if(v.begin() + a, v.begin() + b, [](const auto &el)
		{
			return isPrime(el);
		});
	};

	size_t part_size = v.size() / n_threads, a = 0, b = 0;
	for(size_t thread_id = 0; thread_id < n_threads; thread_id++, a = b)
	{
		b = (thread_id == n_threads - 1) ? v.size() : a + part_size;
		//std::cout << a << ' ' << b << std::endl;
		threads[thread_id] = std::thread(lambda, a, b, thread_id);
	}

	for(auto & t : threads)
		t.join();

	return std::accumulate(res.begin(), res.end(), 0);
}

int main()
{
	std::vector<size_t> v(5'00);
	std::mt19937_64 gen;
	gen.seed(2);
	std::uniform_int_distribution<size_t> d(1,
											std::numeric_limits<size_t>::max()/10);
	for(auto & item : v)
		item = d(gen);

	auto time_one = std::chrono::high_resolution_clock::now();
	auto single_count = single(v);
	//std::cout << block(v, 4) << std::endl;
	auto time_two = std::chrono::high_resolution_clock::now();
	auto single_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_two - time_one).count();
	for(int i = 2; i <= 4; i++)
	{
			time_one = std::chrono::high_resolution_clock::now();
			auto block_count = block(v, i);
			//std::cout << block(v, 4) << std::endl;
			time_two = std::chrono::high_resolution_clock::now();
			auto block_time = std::chrono::duration_cast<std::chrono::milliseconds>(time_two - time_one).count();
	
			std::cout << i << '\t' << single_time << '\t' << block_time << '\t' <<
			single_count << '\t' << block_count << std::endl;
	}
}

```
