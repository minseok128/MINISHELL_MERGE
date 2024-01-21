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

int	wcard_is_matching

int main(void)
{
	printf("%d\n", wildcard_exhaustive("abc", "abcd"));
	printf("%d\n", wildcard_exhaustive("a*a", "abbbbcvdsacda"));
	printf("%d\n", wildcard_exhaustive("*.c", "sdafdfasfasd.c"));
	printf("%d\n", wildcard_exhaustive("abc", "ab"));
	printf("%d\n", wildcard_exhaustive("a*b*c*", "asdsdaasasbasdasdsdaasdcaaaaaa"));
	return (1);
}