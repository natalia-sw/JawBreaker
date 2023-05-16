#pragma once


struct Score
{
	using score_t = unsigned long long;

	score_t total_score{};
	score_t block_score{};
};

constexpr Score::score_t calculate_block_score(size_t block_size)
{
	return block_size * (block_size - 1);
}
