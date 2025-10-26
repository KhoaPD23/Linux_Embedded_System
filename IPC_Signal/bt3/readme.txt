kill() là hàm dùng để gửi tín hiệu đến một tiến trình cụ thể thông qua PID. Trong bài này:
- Tiến trình cha cần chủ động gửi tín hiệu SIGUSR1 cho tiến trình con.
- kill(pid, SIGUSR1) đảm bảo tín hiệu được gửi đúng đến tiến trình con (theo PID).
- Đây là cách chuẩn để giao tiếp giữa các tiến trình trong Unix/Linux.