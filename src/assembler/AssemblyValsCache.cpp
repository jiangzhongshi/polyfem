#include <polyfem/AssemblyValsCache.hpp>
#include <polyfem/MaybeParallelFor.hpp>

namespace polyfem
{
	void AssemblyValsCache::init(const bool is_volume, const std::vector<ElementBases> &bases, const std::vector<ElementBases> &gbases)
	{
		const int n_bases = bases.size();
		cache.resize(n_bases);

		maybe_parallel_for(n_bases, [&](int start, int end, int thread_id) {
			for (int e = start; e < end; ++e)
			{
				cache[e].compute(e, is_volume, bases[e], gbases[e]);
			}
		});
	}

	void AssemblyValsCache::compute(const int el_index, const bool is_volume, const ElementBases &basis, const ElementBases &gbasis, ElementAssemblyValues &vals) const
	{
		if (cache.empty())
			vals.compute(el_index, is_volume, basis, gbasis);
		else
			vals = cache[el_index];
	}

} // namespace polyfem
