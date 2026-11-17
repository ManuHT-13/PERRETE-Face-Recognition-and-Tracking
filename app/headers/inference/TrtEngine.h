#pragma once

#include <memory>
#include <string>
#include <vector>

#include <NvInfer.h>

#include <cuda_runtime_api.h>


class TrtEngine {

private:

	class Logger : public nvinfer1::ILogger {
	public:
		void log(Severity severity, const char* msg) noexcept override;
	};

	Logger logger_;

	std::unique_ptr<nvinfer1::IRuntime> runtime_;
	std::unique_ptr<nvinfer1::ICudaEngine> engine_;
	std::unique_ptr<nvinfer1::IExecutionContext> context_;

	cudaStream_t stream_ = nullptr;

	void* d_in_ = nullptr;
	void* d_out_ = nullptr;

};

