#include <output.hpp>
namespace rangenet {
namespace segmentation {
std::unique_ptr<Net> make_net(const std::string& path,
                              const std::string& backend) {
  // these are the options
  std::vector<std::string> options = {"tensorrt"};

  // check that backend exists
  std::string lc_backend(backend);  // get a copy
  std::transform(lc_backend.begin(), lc_backend.end(), lc_backend.begin(),
                 ::tolower);  // lowercase to allow user to be sloppy
  if (std::find(options.begin(), options.end(), lc_backend) == options.end()) {
    // not found
    std::cerr << "Backend must be one of the following: " << std::endl;
    for (auto& b : options) {
      std::cerr << b << std::endl;
    }
    throw std::runtime_error("Choose a valid backend");
  }

  // make a network
  std::unique_ptr<Net> network;

  // Select backend
  if (lc_backend == "tensorrt") {
#ifdef TENSORRT_FOUND
    // generate net with tf backend
    network = std::unique_ptr<Net>(new NetTensorRT(path));
#endif
  } else {
    // Should't get here but just in case my logic fails (it mostly does)
    throw std::runtime_error(backend + " backend not implemented");
  }

  return network;
}

}  // namespace segmentation
}  // namespace rangenet
