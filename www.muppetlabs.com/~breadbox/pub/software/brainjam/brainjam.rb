class Brainjam < Formula
  desc "Solitaire card game with a full face-up layout"
  homepage "https://www.muppetlabs.com/~breadbox/software/brainjam.html"
  url "https://www.muppetlabs.com/~breadbox/pub/software/brainjam/brainjam-1.0.1.tar.gz"
  sha256 "4eaa839b4ec3e7bc9e16df45863597a174b795ff1237690eb2bc40aa3129c7d4"

  depends_on "pkg-config" => :build
  depends_on "fontconfig"
  depends_on "libpng"
  depends_on "sdl2"
  depends_on "sdl2_ttf"

  def install
    system "./configure", "--prefix=#{prefix}",
                          "--without-ncurses"
    system "make", "install"
  end

  test do
    assert shell_output("#{bin}/brainjam --version").include? version.to_s
    system "#{bin}/brainjam", "--validate"
  end
end
