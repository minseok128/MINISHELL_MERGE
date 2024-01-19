## Summary
PR에 대한 간단한 요약을 작성합니다.

## Description
- PR에서 어떤 사항을 다루었는지에 대한 내용을 리스트로 작성합니다.
- UI에 대한 사항이라면 스크린샷을, 코드에 대한 사항이라면 코드블럭을 첨부해도 좋습니다.

---

### Example (Please Delete when Open Issue)
> ## Summary
> Back-End의 도서검색 관련 API를 구성하였습니다.
>
> ## Description
> - 이후 타 API 작업 시, `Firebase` 관련 연동의 편의를 위해 `FirebaseUtil`을 구성하였습니다. 이는 Client에게 전달되지 않는 Server 항목으로, 기존에 타 프로젝트에서 활용했던 자료를 기반으로 구현하였습니다.
> - 국방도서관 자료검색을 구현하였습니다. `/api/book/getMilLibraryBook/키워드`의 형태로 `GET` 요청을 전송하면, 해당 키워드가 제목에 속한 도서의 정보 리스트가 반환됩니다. 이 과정에서, `Firebase Query`를 활용하고자 하였으나, `String` 자료형에서의 `Contain`을 검사하는 `Query`가 불가한 관계로, Back-End 코드상에서 구현하였습니다.
> - 네이버 도서검색을 구현하였습니다. `/api/book/getNaverBook/키워드`의 형태로 `GET` 요청을 전송하면, 해당 키워드가 제목에 속한 도서의 정보 리스트가 반환됩니다.
>
> - 각 두 함수의 응답 형식은 다음과 같습니다.
> ```json
> {
>   "RESULT_CODE": 200,
>   "RESULT_MSG": "Success",
>   "RESULT_DATA": {
>     "data": [
>       {
>         "author": "길벗R&D",
>         "publisher": "길벗",
>         "title": "2023 시나공 워드프로세서 실기 (자동 채점 프로그램)"
>       },
>       {
>         "author": "길벗R&D",
>         "publisher": "길벗",
>         "title": "2023 시나공 워드프로세서 실기 (자동 채점 프로그램)"
>       }
>     ]
>   }
> }
> ```
