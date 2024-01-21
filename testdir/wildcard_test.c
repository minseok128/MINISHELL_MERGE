/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michang <michang@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:49:26 by michang           #+#    #+#             */
/*   Updated: 2024/01/21 15:49:27 by michang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

int wildcard_exhaustive(const char *pattern, const char *word)
{
	int len_p = strlen(pattern);  // 패턴의 길이
	int len_w = strlen(word);     // 문자열의 길이
	int nth = 0;                  // 현재 위치

	// 첫 번째 조건 - 패턴과 문자열의 앞부분이 정확히 일치하는지 확인
	while (nth < len_p && nth < len_w && pattern[nth] == word[nth]) {
		nth++;
	}

	// 두 번째 조건 - 패턴의 끝에 도달했는지 확인
	if (len_p == nth) {
		return len_w == nth;
	}

	// 세 번째 조건 - `*` 와일드카드 처리
	if (pattern[nth] == '*') {
		for (int skip = 0; skip + nth <= len_w; skip++) {
			if (wildcard_exhaustive(pattern + nth + 1, word + skip + nth)) {
				return (1);
			}
		}
	}

	// 네 번째 조건 - 매치 실패
	return (0);
}

int trtv_is_wild_matching(const char *pattern, const char *name)
{
	int	len_p;
	int	len_n;
	int	now;
	int	skip;
	
	len_p = strlen(pattern);
	len_n = strlen(name);
	now = 0;
	while (now < len_p && now < len_n && pattern[now] == name[now])
		now++;
	if (len_p == len_n)
		return (1);
	if (pattern[now] == '*')
	{
		skip = 0;
		while (skip + now <= len_n)
		{
			if (trtv_is_wild_matching(pattern + now + 1, name + skip + now))
				return (1);
			skip++;
		}
	}
	return (0);
}

int main(void)
{
	printf("%d, %d\n", wildcard_exhaustive("abc", "abcd"), trtv_is_wild_matching("abc", "abcd"));
	printf("%d, %d\n", wildcard_exhaustive("a*a", "abbbbcvdsacda"), trtv_is_wild_matching("a*a", "abbbbcvdsacda"));
	printf("%d, %d\n", wildcard_exhaustive("*.c", "sdafdfasfasd.c"), trtv_is_wild_matching("*.c", "sdafdfasfasd.c"));
	printf("%d, %d\n", wildcard_exhaustive("abc", "ab"), trtv_is_wild_matching("abc", "ab"));
	printf("%d, %d\n", wildcard_exhaustive("a*b*c*", "asdsdaasasbasdasdsdaasdcaaaaaa"), trtv_is_wild_matching("a*b*c*", "asdsdaasasbasdasdsdaasdcaaaaaa"));
	printf("%d, %d\n", wildcard_exhaustive("a *", "a a"), trtv_is_wild_matching("a *", "a a"));
	return (1);
}
