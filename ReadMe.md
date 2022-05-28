# Bài tập lớn cuối kỳ - Game 2048

## 1. Giới thiệu

- 2048 Game  - INT2215 1 - Lập trình nâng cao

- Nguyễn Thị Hiền - 21020316

## 2. Hướng dẫn cài đặt

- Mở terminal, clone Project-2048 về:

  - git clone <https://github.com/Nguyenhiencute/Project-2048.git>

  - cd Project-2048

- Chạy chương trình, nhập vào terminal:

  - make để bắt đầu chơi

## 3. Mô tả chung về trò chơi

- Video demo:

- 2048 chơi trên một lưới vuông 4x4. Mục tiêu của trò chơi là trượt các khối vuông có mang số giống nhau để kết hợp chúng lại và tạo ra khối vuông có giá trị cộng dồn. Trò chơi kết thúc khi các khối vuông không thể trượt được nữa và lấp đầy lưới.

## 4. Mô tả các chức năng cài đặt kèm video minh hoạ:

### 4.1. Menu: 

- Gồm 5 nút: “Play” để bắt đầu game, “ Mute - Unmute” để bật tắt nhạc nền, “- +” để tăng giảm âm thanh nhạc nền, “Quit” để thoát cửa sổ game.

- Nhạc nền và ảnh nền được lấy ngẫu nhiên theo lượt chơi.

- Có hiệu ứng zoom chữ khi di chuyển con trỏ chuột tới các nút

### 4.2. game:

- Mỗi lần di chuyển là một lượt, sử dụng các phím mũi tên: lên - xuống - trái - phải để trượt các ô vuông. 

- Sử dụng phím "Space" để quay lại 1 thao tác. 

- (Sử dụng phím "Left Ctrl/ Left control" để kết thúc trò chơi)

- Mỗi lượt có một khối có giá trị 2 hoặc 4 sẽ xuất hiện ngẫu nhiên (2 xuất hiện ngẫu nhiên nhiều hơn 4). 

- Các khối vuông trượt theo hướng chỉ định cho đến khi chạm đến biên của lưới hoặc chạm vào khối vuông khác. Nếu hai khối vuông có cùng giá trị chạm vào nhau, chúng sẽ kết hợp lại thành một khối vuông có giá trị bằng tổng giá trị hai khối vuông đó.

- Các khối vuông mang giá trị khác nhau sẽ có màu sắc khác nhau.

- "Score:o biết điểm của người chơi. Khi hai khối vuông kết hợp thì người chơi sẽ tăng điểm là giá trị khối vuông mới

- end game sử dụng phím enter/return để bắt đầu lại trò chơi. hiển thị xếp hạng top 5 điểm cao nhất 

## 5. Nguồn tham khảo:

## 6. Các kĩ thuật được sử dụng:

## 7. Kết luận, hướng phát triển và các điều tâm đắc rút ra được khi hoàn thành chương trình

